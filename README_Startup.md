# STM32G070 Startup File — Deep Explanation

---

## 1. Header Directives

These lines appear at the very top of the `.s` file. They are instructions **to the assembler**, not to the CPU.

```
.syntax unified   → use unified ARM/THUMB syntax
.cpu cortex-m0+   → tell assembler which CPU to target
.fpu softvfp      → no hardware FPU, use software float
.thumb            → generate Thumb instructions only
.global           → make symbols visible to the linker
```

**Why Thumb only?**
Cortex-M0+ has no ARM mode at all — it only executes Thumb (16-bit) instructions.
Trying to switch to ARM mode on M0+ causes a HardFault.

**Why softvfp?**
M0+ has no FPU hardware. Floating point operations are handled by software library calls.
This tells the assembler and linker to use software float ABI consistently.

---

## 2. Linker Script Symbols — Where Does Data Live?

The startup file needs to know the exact boundaries of RAM and Flash sections.
It does **not** hardcode these — it reads them from the linker script (`.ld` file).

```
_sidata → start of .data initializers in Flash     (source)
_sdata  → start of .data section in RAM            (destination start)
_edata  → end of .data section in RAM              (destination end)
_sbss   → start of .bss section in RAM
_ebss   → end of .bss section in RAM
_estack → top of RAM                               (initial stack pointer)
```

**Why does .data exist in two places?**

```
FLASH (read-only)                RAM (read-write)
┌────────────────┐               ┌────────────────┐
│ .text (code)   │               │ .data          │
│ .rodata        │               │ int x = 5 ✓    │
│ .data init     │ ─── copy ──►  │ (writable)     │
│ int x = 5      │               ├────────────────┤
│ (source copy)  │               │ .bss           │
└────────────────┘               │ int y = 0      │
                                 │ (zeroed out)   │
                                 └────────────────┘
```

- `.data` — global/static variables **with** initial values → stored in Flash, copied to RAM at boot
- `.bss` — global/static variables **without** initial values → just zeroed in RAM at boot (no Flash copy needed)
- `.text` — your code → stays in Flash, executed directly

---

## 3. Reset_Handler — Step by Step Boot Sequence

This is the actual entry point. The CPU jumps here automatically on every reset.

```
POWER ON / RESET
│
├── Hardware: load SP from vector table slot [0]  (_estack)
├── Hardware: load PC from vector table slot [1]  (Reset_Handler address)
│
└── Reset_Handler begins:
    │
    ├── STEP 1: bl SystemInit
    │           └── set up system clocks before anything else
    │
    ├── STEP 2: Copy .data from Flash to RAM
    │           └── src = _sidata (Flash)
    │               dst = _sdata to _edata (RAM)
    │               loop: copy word by word until dst == _edata
    │
    ├── STEP 3: Zero .bss in RAM
    │           └── fill _sbss to _ebss with 0x00000000
    │               C standard requires uninitialized globals = 0
    │
    ├── STEP 4: bl __libc_init_array
    │           └── run C++ constructors (global objects)
    │               harmless if no C++ used
    │
    └── STEP 5: bl main
                └── your application starts here
                    if main() returns → LoopForever (hang)
```

**Why copy .data before calling main?**
If you have `int x = 5;` as a global variable, the value `5` is stored in Flash.
But `x` must live in RAM (it needs to be writable).
If Reset_Handler does not copy it, `x` contains garbage when `main()` reads it.

**Why zero .bss before calling main?**
The C standard guarantees all uninitialized globals are zero.
RAM power-up state is random. Reset_Handler must manually zero it.
If skipped, `int flag;` may contain `0xDEADBEEF` instead of `0`.

---

## 4. Floating Point — Why softvfp on M0+

Cortex-M0+ has **no FPU unit** in hardware.

```
Cortex-M4 / M7            Cortex-M0+
┌──────────────┐           ┌──────────────┐
│ CPU core     │           │ CPU core     │
│ + FPU unit   │           │ (no FPU)     │
│ VADD.F32     │           │              │
│ runs in 1    │           │ float add    │
│ cycle        │           │ → calls      │
└──────────────┘           │ __aeabi_fadd │
                           │ software fn  │
                           │ ~20-50 cycles│
                           └──────────────┘
```

**What softvfp means in practice:**

| Operation | M4 with FPU | M0+ softvfp |
|---|---|---|
| `float a = b + c` | 1 cycle (VADD.F32) | ~20-50 cycles (library call) |
| `double x = y * z` | few cycles (VMUL.F64) | ~100+ cycles |
| Stack usage | float in FPU register | float on integer stack |
| Code size | small (FPU instructions) | larger (library functions linked in) |

**Practical advice for M0+:**
Avoid float in performance-critical or interrupt code.
Use fixed-point (`int`, `uint32_t` scaled by 100 or 1000) where possible.

---

## 5. Vector Table — The Interrupt Address Book

The vector table is a fixed array at address `0x00000000` (remapped to `0x08000000` Flash on STM32).
Every entry is a **4-byte function pointer**.
The CPU hardware reads this table directly — it is not software.

```
Address       Slot   Symbol               Purpose
──────────────────────────────────────────────────────────
0x00000000    0      _estack              Initial Stack Pointer (not a function)
0x00000004    1      Reset_Handler        Runs on power ON / reset
0x00000008    2      NMI_Handler          Non-maskable interrupt
0x0000000C    3      HardFault_Handler    All fault conditions
0x00000010    4      0 (reserved)         —
0x00000014    5      SVC_Handler          Supervisor call (used by RTOS)
0x00000018    6      PendSV_Handler       Pendable service (RTOS context switch)
0x0000001C    7      SysTick_Handler      1ms system tick (HAL_Delay)
0x00000020    8      WWDG_IRQHandler      Window watchdog
0x00000024    9      ...                  peripheral IRQs continue
```

**How the CPU uses the vector table:**

```
SysTick fires
│
├── CPU saves context (PC, LR, PSR, R0-R3, R12) onto stack
├── CPU reads address from slot [7]  (0x0000001C)
├── CPU jumps to that address
├── ISR runs
└── CPU restores context, resumes where it left off
```

**Slot 0 is special — it is not a function pointer.**
It is loaded directly into the Stack Pointer register (SP/R13) at reset.
It points to `_estack` = top of RAM = the highest RAM address.
Stack grows downward from here.

---

## 6. Weak Aliases — The Safety Net

Every peripheral IRQ handler in the startup file is declared weak:

```
.weak      SysTick_Handler
.thumb_set SysTick_Handler, Default_Handler
```

**What this means:**
- `.weak` → this symbol has low priority; any strong definition elsewhere overrides it
- `.thumb_set` → makes `SysTick_Handler` an alias pointing to `Default_Handler`'s address

**Linker resolution rules:**

```
strong vs weak   → strong always wins
strong vs strong → linker ERROR (multiple definition)
weak   vs weak   → first one encountered wins
```

**Without your handler (weak active):**
```
Vector table slot [7] = Default_Handler address
SysTick fires → jumps to Default_Handler → while(1) → CPU hangs
```

**With your handler (strong overrides):**
```
Vector table slot [7] = your SysTick_Handler address
SysTick fires → jumps to your function → HAL_IncTick() runs
```

**Map file proof — before defining SysTick_Handler:**
```
0x08000234   Default_Handler
0x08000234   NMI_Handler         ← same address = alias
0x08000234   HardFault_Handler   ← same address = alias
0x08000234   SysTick_Handler     ← same address = alias
```

**Map file proof — after defining SysTick_Handler in your code:**
```
0x08000234   Default_Handler     ← still exists
0x08000320   SysTick_Handler     ← now has its own unique address
```

---

## 7. Default_Handler

```
Default_Handler:
    b Default_Handler    ← branch to itself, infinite loop
```

- Only **2 bytes** in Flash
- Acts as a catch-all for any interrupt that fires without a user handler
- CPU hangs here visibly — useful for debugging (PC stuck at this address in debugger)
- Without this, an unhandled IRQ would jump to a random address → unpredictable behavior

---

## 8. Complete Boot Flow Summary

```
POWER ON
│
├── Hardware loads SP  ← _estack  (top of RAM)
├── Hardware loads PC  ← Reset_Handler address
│
└── Reset_Handler
    ├── SystemInit()              set up clocks
    ├── Copy .data Flash → RAM    initialize global variables
    ├── Zero .bss in RAM          C standard: globals default to 0
    ├── __libc_init_array()       C++ global constructors
    └── main()
         │
         ├── HAL_Init() sets up SysTick (1ms tick)
         │
         └── every 1ms: SysTick fires
              ├── your SysTick_Handler defined? → your code
              └── not defined?                  → Default_Handler → hang
```
