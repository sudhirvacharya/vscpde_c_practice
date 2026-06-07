# ARM Architecture — Exception, Interrupt & Trap Notes

---

## 1. Core Definitions

| Term | Definition |
|---|---|
| **Exception** | Any event that forces the processor to halt normal execution and run a privileged handler routine |
| **Interrupt** | Asynchronous external hardware event (peripheral) requiring CPU attention |
| **Trap** | A specific type of **software-triggered** exception — intentionally passes control to OS or debugger |

> **Key insight:** Trap is a *subset* of Exception. All traps are exceptions, but not all exceptions are traps.

---

## 2. ARM Exception Categories

### 2.1 Interrupts (IRQ / FIQ)
- **Type:** Asynchronous — happen anytime, from external hardware
- **Source:** Timer, UART, DMA, GPIO, SPI, ADC peripherals
- **Managed by:** NVIC (Cortex-M) or GIC (Cortex-A)
- **Examples on STM32:** `USART1_IRQHandler`, `DMA1_Channel1_IRQHandler`, `TIM2_IRQHandler`

### 2.2 Aborts
- **Type:** Synchronous — triggered by failed memory access or instruction fetch
- **Two types:**
  - **Prefetch Abort** — failed instruction fetch (bad PC address)
  - **Data Abort** — failed data read/write (bad memory address)
- **Cortex-M equivalent:** HardFault (M0+ collapses all aborts here)

### 2.3 Supervisor Calls — SVC / SMC / HVC *(these are TRAPS)*
- **Type:** Synchronous — software deliberately triggers them
- **Purpose:** Cross privilege boundary to request OS or hypervisor service

| Instruction | Full Name | Used by |
|---|---|---|
| `SVC` | Supervisor Call | User code → OS (FreeRTOS, Linux) |
| `SMC` | Secure Monitor Call | Normal world → Secure world (TrustZone) |
| `HVC` | Hypervisor Call | Guest OS → Hypervisor |

### 2.4 Undefined Instructions
- **Type:** Synchronous — CPU encounters unsupported opcode
- **Common use:** Emulate missing hardware (e.g., FPU instructions on M0+)
- **Cortex-M:** Triggers HardFault

### 2.5 Reset
- **Type:** Highest priority exception
- **Trigger:** Power-on, NRST pin, software reset (`NVIC_SystemReset()`)
- **Priority:** Fixed — cannot be changed, always runs first

---

## 3. Exception vs Trap — Key Difference

| Property | Exception | Trap |
|---|---|---|
| **Broader category** | Yes — covers all events | No — specific subtype |
| **Trigger** | Hardware condition OR software | Software only (deliberate) |
| **Expected?** | Not always | Always — programmer intended |
| **Examples** | HardFault, Reset, NMI, IRQ | SVC, BKPT, INT 0x80, ECALL |
| **Synchronous?** | Not always (IRQ is async) | Always synchronous |

> **Simple rule:**
> - Exception = broad umbrella (hardware + software events)
> - Trap = deliberate software jump into privileged mode
> - Interrupt = asynchronous hardware signal via NVIC

---

## 4. Exception Lifecycle — What CPU Does

When any exception/interrupt/trap fires, ARM follows this exact sequence:

```
Step 1 — STATE PRESERVATION
   Current PC and CPSR saved
   → Cortex-M:  auto-pushed to stack (xPSR, PC, LR, R12, R3-R0)
   → Cortex-A:  saved to LR and SPSR of new exception mode

Step 2 — VECTOR LOOKUP
   CPU reads vector table
   → Cortex-M:  table at 0x00000000 (or VTOR address)
   → Cortex-A:  table at 0x00000000 or 0xFFFF0000

Step 3 — EXECUTION
   CPU jumps to handler address
   Runs in privileged Handler Mode (Cortex-M)
   or privileged exception mode (Cortex-A: SVC/ABT/IRQ/UND mode)

Step 4 — RETURN
   → Cortex-M:  BX LR with EXC_RETURN value
                hardware auto-unstacks 8 registers
   → Cortex-A:  ERET instruction
                restores PC and CPSR from LR and SPSR
   Normal execution resumes
```

---

## 5. Cortex-M Specific — Vector Table Layout

```
Address 0x00000000  →  _estack            (Initial Stack Pointer)
Address 0x00000004  →  Reset_Handler      ← Exception  (highest priority)
Address 0x00000008  →  NMI_Handler        ← Exception
Address 0x0000000C  →  HardFault_Handler  ← Exception  (all faults on M0+)
Address 0x0000002C  →  SVC_Handler        ← TRAP
Address 0x00000038  →  PendSV_Handler     ← Exception  (RTOS context switch)
Address 0x0000003C  →  SysTick_Handler    ← Exception  (RTOS tick)
─────────────────────────────────────────────────────
Address 0x00000040  →  WWDG_IRQHandler    ← Interrupt  IRQ0
Address 0x00000044  →  RTC_IRQHandler     ← Interrupt  IRQ1
...
Address 0x000000B8  →  USART1_IRQHandler  ← Interrupt  IRQ22
Address 0x000000BC  →  SPI1_IRQHandler    ← Interrupt  IRQ20
```

---

## 6. Cortex-M0+ Fault Collapse

On **Cortex-M0+** (STM32G070), there is only ONE fault handler:

```
Divide by zero      ──┐
Bad memory access   ──┤──► HardFault_Handler  (only fault handler)
Undefined opcode    ──┘

No MemManage, No BusFault, No UsageFault on M0+
All collapse into HardFault
```

On **Cortex-M3/M4/M7** these are separate:
- MemManage_Handler
- BusFault_Handler
- UsageFault_Handler
- HardFault_Handler

---

## 7. Trap Examples Across Architectures

| Platform | Instruction | Purpose |
|---|---|---|
| ARM Cortex-M | `SVC #0` | FreeRTOS system call |
| ARM Cortex-M | `BKPT #0` | Debugger breakpoint trap |
| ARM Cortex-A | `SVC #0` | Linux system call |
| ARM Cortex-A | `HVC #0` | Hypervisor call |
| ARM Cortex-A | `SMC #0` | TrustZone secure monitor call |
| x86 Linux old | `INT 0x80` | Kernel system call (Ring3 → Ring0) |
| x86 Linux new | `SYSCALL` | Kernel system call (faster) |
| x86 debugger | `INT 3` | Debugger breakpoint |
| RISC-V | `ECALL` | Machine mode service call |

---

## 8. One-Line Memory Rules

```
Exception  →  CPU forced to stop — hardware or software caused it
Interrupt  →  Peripheral rang the doorbell — NVIC routes it to CPU
Trap       →  You deliberately pressed the emergency button — software only
```

```
Interrupt ──────────────────────────────────► subset of Exception
Trap ────────────────────────────────────────► subset of Exception
All three use same mechanism: vector table + auto-stack + Handler Mode
```

---

## 9. Advanced Topics (For Later Study)

- **Vector Catch** — Debugger trap that intercepts specific exceptions (HardFault, Reset) before handler runs; used in TRACE32 / OpenOCD
- **Floating-Point Trap Handling** — IEEE 754 FP exceptions (divide by zero, overflow, invalid op) on Cortex-M4/M7 with FPU
- **Hypervisor Trap (HVC)** — Cortex-A only; guest OS traps into hypervisor layer (used in KVM, Xen)
- **TrustZone SMC** — Secure Monitor Call; normal world apps trap into secure world (used in OP-TEE)

---

*Sources: ARM Developer Documentation, Memfault Interrupt Blog, ARM Cortex-M0+ TRM*
*Reference: STM32G070 RM0454 Section 11.3*
