# Program Status Register (PSR) — ARM Cortex-M

---

## Overview

The PSR is a 32-bit register that holds the current processor state. It is composed of three overlapping sub-registers accessible individually or combined.

```
PSR = xPSR (combined view)
       ├── APSR  — Application Program Status Register
       ├── IPSR  — Interrupt Program Status Register
       └── EPSR  — Execution Program Status Register
```

Access via `MRS` / `MSR` instructions:

```asm
MRS r0, xPSR     ; read combined PSR into r0
MRS r0, APSR     ; read only APSR
MRS r0, IPSR     ; read only IPSR
MRS r0, EPSR     ; read only EPSR (always reads as 0 in user code)
```

---

## xPSR Bit Layout (32-bit)

```
Bit:  31 30 29 28 27  26:25  24  23:20  19:16  15:10   9    8:0
       N  V  C  Z  Q  ICI/IT  T   ---   GE     ICI/IT  ---  ISR_NUM
       |-----------|          |                               |-----|
          APSR               EPSR                             IPSR
```

---

## APSR — Application Program Status Register

Holds **ALU condition flags**. Used by conditional instructions (`BEQ`, `BNE`, `BGT`, etc.).

| Bit | Flag | Name           | Set When                          |
|-----|------|----------------|-----------------------------------|
| 31  | N    | Negative       | Result was negative (MSB = 1)     |
| 30  | Z    | Zero           | Result was zero                   |
| 29  | C    | Carry          | Unsigned overflow / carry-out     |
| 28  | V    | Overflow       | Signed overflow                   |
| 27  | Q    | Saturation     | Saturation occurred (DSP ops)     |
| 19:16 | GE | Greater-Equal | SIMD compare result (Cortex-M4+) |

### Example

```c
// After: SUBS r1, r0, r1
// if result == 0 → Z flag set → BEQ branches
```

```asm
CMP   r0, r1      ; sets N, Z, C, V based on r0 - r1
BEQ   equal       ; branch if Z=1
```

---

## IPSR — Interrupt Program Status Register

Holds the **exception number** of the currently executing exception.

| Bits | Field   | Meaning                                      |
|------|---------|----------------------------------------------|
| 8:0  | ISR_NUM | Current exception number (0 = Thread mode)   |

### Exception Number Table

| ISR_NUM | Exception         |
|---------|-------------------|
| 0       | Thread mode (no exception) |
| 1       | Reset             |
| 2       | NMI               |
| 3       | HardFault         |
| 4       | MemManage         |
| 5       | BusFault          |
| 6       | UsageFault        |
| 11      | SVCall            |
| 14      | PendSV            |
| 15      | SysTick           |
| 16+     | IRQ0, IRQ1, ...   |

### Usage in Code

```c
// Check if running in an ISR or Thread mode
uint32_t ipsr;
__asm volatile ("MRS %0, IPSR" : "=r"(ipsr));

if (ipsr == 0) {
    // Thread mode — use SVC for privileged ops
} else {
    // Handler mode — already privileged
}
```

---

## EPSR — Execution Program Status Register

Holds **execution state bits**. Cannot be read directly by software (reads as 0).

| Bits  | Field  | Meaning                                          |
|-------|--------|--------------------------------------------------|
| 24    | T      | Thumb state bit — **must always be 1** on Cortex-M |
| 26:25, 15:10 | ICI/IT | If-Then / Interrupt-Continuable state   |

### T Bit (Thumb)

- Cortex-M **only supports Thumb instructions**
- T bit must always be `1`
- If T = 0 → **UsageFault** (INVSTATE)
- This is why function pointers and vector table entries must have **bit 0 set** (ORR with 1)

```c
// Vector table entry — bit 0 must be 1 (Thumb indicator)
void (* const vectors[])(void) __attribute__((section(".isr_vector"))) = {
    (void *)&_estack,
    Reset_Handler,    // address stored as addr | 0x1
    NMI_Handler,
    HardFault_Handler,
    // ...
};
```

### IT Bits (If-Then Block)

Tracks the state of an IT instruction block in Thumb-2. Managed by hardware during conditional instruction sequences. Not directly user-manipulated.

---

## Combined xPSR Read

```asm
MRS r0, xPSR
```

Reads all three sub-registers in one shot. Useful for:
- Saving full processor state in context switch
- Debugging (TRACE32: `r xPSR`)

---

## Accessing in C (CMSIS)

```c
#include "cmsis_gcc.h"   // or core_cm4.h

uint32_t apsr = __get_xPSR();    // full xPSR
uint32_t ipsr_val = __get_IPSR(); // ISR number only

// Check if in IRQ context
if (__get_IPSR() != 0) {
    // Inside exception handler
}
```

---

## CONTROL Register (Related — Not PSR)

Often confused with PSR. Separate register controlling:

| Bit | Name   | Function                              |
|-----|--------|---------------------------------------|
| 0   | nPRIV  | 0=Privileged Thread, 1=Unprivileged   |
| 1   | SPSEL  | 0=use MSP, 1=use PSP (Thread mode)    |
| 2   | FPCA   | FP context active (Cortex-M4F only)   |

```asm
MRS r0, CONTROL
MSR CONTROL, r0
ISB               ; always execute ISB after MSR CONTROL
```

---

## Quick Reference

| Register | Readable | Writable | Key Info                        |
|----------|----------|----------|---------------------------------|
| APSR     | Yes      | Yes      | N, Z, C, V, Q flags             |
| IPSR     | Yes      | No       | Current exception number        |
| EPSR     | No (0)   | No       | T bit, IT state                 |
| xPSR     | Yes      | Partial  | Combined view of all three      |

---

## Key Rules to Remember

1. **T bit must always be 1** on Cortex-M — never clear it.
2. **IPSR == 0** means Thread mode; non-zero means Handler mode.
3. **APSR flags** drive all conditional branching — set by `CMP`, `TST`, `ADDS`, etc.
4. **EPSR cannot be read** — reads as 0; written only by hardware.
5. Always execute **ISB** after writing CONTROL register.
