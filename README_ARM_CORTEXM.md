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


# 30 Must-Know ARM Cortex-M Architecture Questions
### Embedded Systems Interview Series — For Every Embedded Engineer

---

## 1. Microcontroller vs Microprocessor?
- **MCU:** CPU + RAM + Flash + Peripherals in one chip. Low cost, low power. Used in Embedded systems.
- **MPU:** Only CPU. Costly, high power. Used in PCs/Laptops.

## 2. Von Neumann vs Harvard Architecture?
- **Von Neumann:** Single shared Bus for both CPU and Memory (instructions + data together).
- **Harvard:** Separate Instr Memory and Data Memory paths from CPU.

## 3. Why do most MCUs use Harvard architecture?
Instruction fetch and data access happen simultaneously. This improves speed and efficiency.

## 4. RISC vs CISC? Which does Cortex-M follow?
- **RISC:** Simple instructions, fixed size, fewer cycles. Example: `ADD R0,R1,R2`
- **CISC:** Complex instructions, variable size, multiple cycles. Example: `MUL + STORE + LOAD`
- ARM Cortex-M follows **RISC**.

## 5. ARM Cortex-M pipeline stages?
Most Cortex-M3/M4 use a 3-stage pipeline: **Fetch → Decode → Execute**.

## 6. What is pipelining and why does it improve performance?
CPU overlaps multiple instructions so it is always busy. This increases throughput — while Instruction 1 is in Execute, Instruction 2 is in Decode, and Instruction 3 is in Fetch, all in the same cycle.

## 7. What are pipeline hazards? Name the three types.
1. **Data Hazard** — Dependency between instructions
2. **Control Hazard** — Due to branch/jump instructions
3. **Structural Hazard** — Hardware resource conflict

## 8. Difference between Cortex-M0, M3, M4, M7?
| Core | Features |
|---|---|
| M0 | Basic, Low power |
| M3 | Better performance |
| M4 | DSP + FPU |
| M7 | Highest performance, Cache, Dual issue |

## 9. What is the NVIC and what is its role?
NVIC (Nested Vectored Interrupt Controller):
- Handles interrupts
- Sets priority
- Supports nesting
- Fast interrupt response

## 10. Difference between MSP and PSP?
- **MSP (Main Stack Pointer):** Used after reset. Used by interrupts.
- **PSP (Process Stack Pointer):** Used by application tasks. Common in RTOS.

## 11. What is the vector table and where is it located?
Contains:
- Initial Stack Pointer
- Reset Handler
- Interrupt addresses

Located at `0x00000000` (or Flash base).

## 12. What happens during a reset sequence on ARM Cortex-M?
1. CPU reads Initial SP
2. Loads Reset Handler address
3. Jumps to `Reset_Handler`
4. Initializes data/BSS
5. Calls `main()`

## 13. What is the reset vector and how does the CPU find it?
Reset vector is the address of `Reset_Handler`. CPU reads it from Vector Table Offset = `0x04`.

## 14. What are Thread mode vs Handler mode?
- **Thread Mode:** Normal program execution (`main()`).
- **Handler Mode:** Executes interrupts and exceptions.

## 15. What are the different operating modes in Cortex-M?
- Thread Mode
- Handler Mode

Thread mode can run as: Privileged or Unprivileged.

## 16. What is the xPSR register and what does it contain?
xPSR = Combined Program Status Register. Contains:
- APSR + IPSR + EPSR

Stores flags, exception number, execution state.

## 17. What are APSR, IPSR, and EPSR?
- **APSR:** Arithmetic flags (N, Z, C, V)
- **IPSR:** Current interrupt number
- **EPSR:** Thumb state, execution info

## 18. Privileged vs Unprivileged execution?
**Privileged:**
- Full hardware access
- Can access system registers

**Unprivileged:**
- Limited access
- Cannot modify critical registers

## 19. What is a peripheral bus bridge?
It connects the high-speed AHB bus to the low-speed APB bus. It translates AHB to APB transactions.

## 20. What is the role of a clock tree?
Distributes system clock to different modules (CPU, buses, timers, peripherals) and allows each to run at required frequency. Helps in performance & power optimization.

## 21. What is a bus matrix in an SoC?
Connects multiple masters (CPU, DMA, USB, Ethernet) to multiple slaves (RAM, Flash, Peripherals).

## 22. What is a PLL (Phase Locked Loop) used for?
PLL multiplies a low frequency reference clock (e.g. 8MHz crystal) to generate a higher, stable system clock (e.g. 72MHz, 168MHz, etc).

## 23. Explain AHB, APB, and AXI buses?
| Feature | AHB | APB |
|---|---|---|
| Speed | High | Low |
| Burst Transfer | Yes | No |
| Pipeline | Yes | No |
| Usage | CPU, Memory | Peripherals |

## 24. What is a Brown-Out Reset (BOR)?
BOR monitors the supply voltage. If voltage drops below a safe threshold, MCU automatically resets to prevent wrong execution or memory corruption.

## 25. What is a Power-On Reset (POR)?
POR is generated when the MCU is powered up. It keeps the MCU in reset until the supply voltage becomes stable, then starts normal operation from the reset vector.

## 26. Crystal oscillator vs Internal RC oscillator?
| | Crystal Oscillator | Internal RC Oscillator |
|---|---|---|
| Accuracy | High accuracy | Low accuracy |
| Stability | Stable | Less stable |
| Setup | Needs external component | Built-in |
| Cost | High cost | Low cost |

## 27. What is jitter in a clock signal?
Jitter is the small variation in the timing of clock edges from their ideal positions. Excessive jitter affects performance and reliability.

## 28. Synchronous vs Asynchronous Reset?
**Synchronous Reset:**
- Applied on a clock edge
- Needs clock to run

**Asynchronous Reset:**
- Takes effect immediately
- Independent of clock

---

*Note: The source infographic image was cropped before questions 29 and 30. If you can share the rest of the image (or a fuller version), I can add the remaining two questions to this file.*
