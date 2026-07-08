# ARM Cortex-M Embedded Flashcards (Q1–Q20)

## 1. What is the difference between cold boot and warm boot?
- **Cold boot:** Power is completely OFF and turned ON again (POR). Full fresh start, RAM is cleared.
- **Warm boot:** System is reset without removing power (reset button or software reset). RAM may retain some data.

## 2. What are General Purpose Registers in ARM Cortex-M (R0–R12)?
- Cortex-M has 13 general purpose registers (R0 to R12).
- These are used to store variables, temporary values, calculations, etc., before writing to memory.

## 3. What is the Link Register (LR) used for?
- LR (R14) stores the return address when a function is called.
- After the function completes, CPU returns to that address stored in LR.

## 4. What is the Program Counter (PC) and how does it behave during branches?
- PC (R15) holds the address of the current instruction.
- Normally, it points to the next instruction.
- During branch/jump/function call, PC is updated to the new target address.

## 5. What is the Stack Pointer (SP) and how does the stack grow in ARM?
- SP points to the top of the stack.
- In ARM Cortex-M, stack grows from high address to low address (downward growth).
- Stack follows LIFO (Last In First Out).

## 6. Explain the exception entry and exit sequence in Cortex-M.
- On exception entry, CPU automatically stacks 8 registers (R0–R3, R12, LR, PC, xPSR) on the stack. ISR runs.
- On exit, CPU un-stacks those registers and restores the previous context. This is automatic.

## 7. What is tail-chaining in interrupt handling?
- When two interrupts occur back-to-back, CPU skips the unstack/restack process and directly switches to the next ISR. This reduces latency.

## 8. What is late arrival in NVIC interrupt handling?
- If a higher priority interrupt arrives while a lower priority one is being processed (before stacking completes), NVIC switches to the higher priority ISR immediately. This is called late arrival.

## 9. What is a fault handler? Name different fault types in Cortex-M.
- Fault handler is used when something goes wrong.
- Fault types: HardFault, MemManage Fault, BusFault, UsageFault.

## 10. What is HardFault, MemManage, BusFault, and UsageFault?
- **HardFault** — General/catastrophic fault (default fallback)
- **MemManage** — Illegal memory access (MPU violation)
- **BusFault** — Bus level error (wrong address access)
- **UsageFault** — Illegal instruction execute (e.g., divide by zero)

## 11. What causes a stack overflow at the hardware level?
- When SP goes below the allocated stack limit, it overwrites adjacent memory (heap/data).
- This causes silent corruption or crash.

## 12. What is unaligned memory access and how does Cortex-M handle it?
- Accessing 4-byte data at an address not multiple of 4 is called unaligned access.
- Cortex-M3/M4 can handle it (but slower).
- Cortex-M0 throws a fault.


## 15. What is a memory map and why is it important in embedded systems?
- Memory map is the layout of Flash, RAM and peripherals in the address space.
- It helps the CPU access the right resource using correct addresses.

## 16. What are memory-mapped peripherals?
- Peripherals (GPIO, UART, Timer, ADC, etc.) are assigned specific addresses in memory.
- Read/write to these addresses controls the peripherals.


