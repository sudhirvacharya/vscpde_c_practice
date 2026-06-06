# STM32G070 Linker Script — Deep Explanation

---

## What is a Linker Script?

After the compiler turns your `.c` files into object files (`.o`), the **linker** combines them into one final binary. But it needs to know:

- How much Flash and RAM does this chip have?
- Where exactly should code go?
- Where should global variables go?
- How much space to reserve for stack and heap?

The linker script (`.ld` file) answers all of these questions. It is the **map of the MCU's memory**.

---

## Memory Layout of STM32G070RB

```
STM32G070RB Physical Memory
┌─────────────────────────────┐  0x08000000 + 128K
│                             │
│         FLASH  128K         │  read + execute only
│         (rx)                │
│                             │
├─────────────────────────────┘  0x08000000  ← code starts here

┌─────────────────────────────┐  0x20000000 + 36K
│         RAM    36K          │  read + write + execute
│         (xrw)               │
│                             │
└─────────────────────────────┘  0x20000000  ← RAM starts here
```

---

## Block 1 — Entry Point

```
ENTRY(Reset_Handler)
```

**What it does:**
Tells the linker which function is the very first thing that runs.
When the debugger connects or the chip resets, execution starts at `Reset_Handler`.
This also prevents the linker from discarding `Reset_Handler` as "unused code".

---

## Block 2 — Stack Top Address

```
_estack = ORIGIN(RAM) + LENGTH(RAM);
```

**What it does:**
Calculates the top of RAM and names it `_estack`.

```
RAM starts at  0x20000000
RAM length     36K = 36864 bytes = 0x9000

_estack = 0x20000000 + 0x9000 = 0x20009000  ← top of RAM
```

The stack grows **downward** from this address.
The startup file places `_estack` in vector table slot [0] so the CPU loads it into SP on reset.

---

## Block 3 — Heap and Stack Size Minimums

```
_Min_Heap_Size  = 0x200;   →  512 bytes minimum heap
_Min_Stack_Size = 0x400;   →  1024 bytes minimum stack
```

**What it does:**
These are not the actual heap/stack — they are **minimum size guarantees**.
Later in `._user_heap_stack`, the linker checks that enough RAM is left for both.
If your code uses too much RAM and squeezes these out, the linker throws an error at build time — not a random crash at runtime.

**Stack vs Heap:**

```
RAM layout (grows toward each other)
┌────────────────────────────┐  _estack (0x20009000)
│   Stack                    │  grows ↓  (function calls, local vars)
│   ↓  ↓  ↓                  │
│                            │
│   ↑  ↑  ↑                  │
│   Heap                     │  grows ↑  (malloc, dynamic alloc)
├────────────────────────────┤
│   .bss   (zeroed globals)  │
├────────────────────────────┤
│   .data  (init globals)    │
└────────────────────────────┘  0x20000000
```

---

## Block 4 — MEMORY Region Definitions

```
MEMORY
{
  RAM    (xrw) : ORIGIN = 0x20000000, LENGTH = 36K
  FLASH  (rx)  : ORIGIN = 0x08000000, LENGTH = 128K
}
```

**What it does:**
Declares the two physical memory regions of this specific chip.
All section placements later (`>FLASH`, `>RAM`) refer to these names.

**Permissions:**

| Symbol | Meaning |
|---|---|
| `r` | readable |
| `w` | writable |
| `x` | executable |

Flash is `rx` — code can run from it, but it cannot be written at runtime (without special Flash write routines).
RAM is `xrw` — readable, writable, and executable (needed for RamFunc feature).

---

## Block 5 — `.isr_vector` Section

```
.isr_vector : { } >FLASH
```

**What it does:**
Places the vector table as the **very first thing** in Flash at `0x08000000`.

This is critical — the CPU hardware reads the vector table from `0x00000000` on reset (which maps to `0x08000000` on STM32). If the vector table is not at the start of Flash, the chip cannot boot.

`KEEP` prevents the linker from discarding the vector table even if no code directly "calls" it.

```
Flash layout after .isr_vector:
0x08000000  [ _estack address     ]  slot 0
0x08000004  [ Reset_Handler addr  ]  slot 1
0x08000008  [ NMI_Handler addr    ]  slot 2
...
```

---

## Block 6 — `.text` Section (Your Code)

```
.text : { } >FLASH
```

**What it does:**
Places all compiled code (functions) into Flash, right after the vector table.

**What goes inside:**

| Sub-section | Contents |
|---|---|
| `.text` | all your compiled C functions |
| `.text*` | inline functions, template instances |
| `.glue_7` / `.glue_7t` | ARM↔Thumb interworking stubs (not used on M0+ but included for compatibility) |
| `.eh_frame` | exception handling frame info |
| `.init` / `.fini` | C runtime init/fini routines |

`_etext` marks the end of the code region. The startup file uses this to know where `.data` initializers end in Flash.

---

## Block 7 — `.rodata` Section (Constants)

```
.rodata : { } >FLASH
```

**What it does:**
Places all read-only data into Flash.

**Examples of what lands here:**

```c
const int table[] = {1, 2, 3, 4};   → .rodata
const char msg[] = "Hello";         → .rodata
"string literal"                    → .rodata
```

These never need to be in RAM because they are never written to — Flash is fine.

---

## Block 8 — `.ARM.extab` and `.ARM` Sections

```
.ARM.extab : { } >FLASH
.ARM       : { } >FLASH
```

**What it does:**
These hold C++ exception unwinding tables.

- `.ARM.extab` — exception handling instructions per function
- `.ARM.exidx` — index table mapping function addresses to their unwind data

On M0+ with no C++ exceptions, these sections are usually empty.
`__exidx_start` and `__exidx_end` symbols are used by the C++ runtime if needed.
They are kept in Flash since they are read-only metadata.

---

## Block 9 — Constructor/Destructor Arrays

```
.preinit_array : { } >FLASH
.init_array    : { } >FLASH
.fini_array    : { } >FLASH
```

**What it does:**
These are tables of **function pointers** for C++ global object constructors and destructors.

```
.preinit_array  → functions that run before global constructors
.init_array     → global constructors  (run by __libc_init_array in startup)
.fini_array     → global destructors   (run on exit, rarely used on embedded)
```

**Flow in startup:**
```
Reset_Handler
    └── bl __libc_init_array
            └── reads .init_array table
                    └── calls each constructor function pointer in order
```

`PROVIDE_HIDDEN` creates the start/end symbols but hides them from external object files — they are only used internally by the C runtime.

`KEEP` prevents linker from discarding these even though no code calls them by name.

---

## Block 10 — `_sidata` Symbol

```
_sidata = LOADADDR(.data);
```

**What it does:**
`_sidata` is the Flash address where `.data` initial values are stored.

The `.data` section lives in RAM at runtime, but its initial values must be stored somewhere permanent — Flash. `LOADADDR(.data)` gives the Flash address of that stored copy.

The startup file uses this:
```
source      = _sidata   (Flash — where initial values are stored)
destination = _sdata    (RAM   — where variables must live)
copy until  = _edata    (RAM   — end of .data region)
```

---

## Block 11 — `.data` Section (Initialized Global Variables)

```
.data : { } >RAM AT> FLASH
```

**What it does:**
This is the most important dual-address section.

`>RAM` — at **runtime**, `.data` variables live in RAM (they need to be writable)
`AT> FLASH` — at **load time**, their initial values are stored in Flash

```c
int x = 5;     → lives in RAM at runtime, initial value 5 stored in Flash
int y = 100;   → same
```

**Without the startup copy, `x` would be garbage in RAM.**

**`.RamFunc` subsection:**
Functions marked `__attribute__((section(".RamFunc")))` are also copied here.
These are functions that must execute from RAM — typically Flash write routines
(you cannot execute from Flash while writing to it).

```
Flash                              RAM
┌──────────────────┐               ┌──────────────────┐
│ _sidata          │               │ _sdata           │
│ [5]  ← x init   │ ──copy──►     │ x = 5 (writable) │
│ [100]← y init   │               │ y = 100          │
│ _edata (Flash)   │               │ _edata (RAM)     │
└──────────────────┘               └──────────────────┘
```

---

## Block 12 — `.bss` Section (Uninitialized Global Variables)

```
.bss : { } >RAM
```

**What it does:**
Places all zero-initialized globals and statics into RAM.

```c
int counter;          → .bss  (no initial value → must be 0 per C standard)
static int flag;      → .bss
```

**Key difference from `.data`:**
`.bss` has **no copy in Flash** — there is nothing to copy.
The startup file just zeros out the region from `_sbss` to `_ebss`.

`*(COMMON)` — picks up tentative definitions (uninitialized globals declared without `extern`).

```
RAM
┌──────────────────┐  _sbss
│ counter = 0      │  ← startup zeros this entire region
│ flag    = 0      │
│ ...              │
└──────────────────┘  _ebss
```

---

## Block 13 — `._user_heap_stack` Section

```
._user_heap_stack : { } >RAM
```

**What it does:**
Reserves space in RAM for heap and stack and **verifies at link time** that enough RAM exists.

```
RAM from bottom to top:
┌──────────────────┐  0x20000000
│ .data            │
├──────────────────┤
│ .bss             │
├──────────────────┤  ← end / _end  (heap starts here)
│ Heap  (512 B)    │  grows ↑
├──────────────────┤
│ Stack (1024 B)   │  grows ↓
├──────────────────┤
│ (must fit here)  │
└──────────────────┘  _estack = 0x20009000
```

`PROVIDE(end = .)` and `PROVIDE(_end = .)` — `malloc` uses `end` to know where heap starts.
If `.data + .bss + heap_min + stack_min` exceeds 36K, the linker errors at build time.

---

## Block 14 — `/DISCARD/`

```
/DISCARD/ :
{
  libc.a ( * )
  libm.a ( * )
  libgcc.a ( * )
}
```

**What it does:**
Throws away debug and unwind sections from the standard C, math, and GCC support libraries.
These sections (exception tables, debug frames) are not needed on a bare-metal embedded target and would waste Flash space.

---

## Block 15 — `.ARM.attributes`

```
.ARM.attributes 0 : { *(.ARM.attributes) }
```

**What it does:**
Collects ABI (Application Binary Interface) metadata from all object files.
Contains information like: CPU type, Thumb version, FPU type, endianness.
Used by debuggers and loaders — not loaded onto the chip.
The `0` address means it has no runtime address — it exists only in the ELF file.

---

## Complete Memory Map After Linking

```
FLASH (0x08000000)                    RAM (0x20000000)
┌──────────────────────┐              ┌──────────────────────┐
│ .isr_vector          │              │ .data                │ ← copied from Flash by startup
│ (vector table)       │              │ int x = 5            │
├──────────────────────┤              ├──────────────────────┤
│ .text                │              │ .bss                 │ ← zeroed by startup
│ (your code)          │              │ int counter = 0      │
├──────────────────────┤              ├──────────────────────┤
│ .rodata              │              │ Heap                 │ ← malloc uses this
│ const table[]        │              │ (min 512 B)          │
├──────────────────────┤              ├──────────────────────┤
│ .ARM.extab / .exidx  │              │ Stack                │ ← grows downward
├──────────────────────┤              │ (min 1024 B)         │
│ .init_array          │              └──────────────────────┘ _estack = 0x20009000
│ .fini_array          │
├──────────────────────┤
│ .data init values    │ ← _sidata points here (source for RAM copy)
│ int x = 5 stored     │
└──────────────────────┘
```

---

## Key Symbols Summary

| Symbol | Value | Used By |
|---|---|---|
| `_estack` | top of RAM | startup → initial SP in vector table |
| `_sidata` | Flash address of .data init values | startup → source of copy loop |
| `_sdata` | RAM start of .data | startup → destination start |
| `_edata` | RAM end of .data | startup → destination end |
| `_sbss` | RAM start of .bss | startup → zero fill start |
| `_ebss` | RAM end of .bss | startup → zero fill end |
| `end` / `_end` | end of .bss | malloc → heap start |
| `_etext` | end of .text in Flash | — |
