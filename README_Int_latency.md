# Interrupt Latency — Complete Guide

---

## 1. What is Interrupt Latency?

**Interrupt Latency** is the time elapsed from the moment an interrupt signal is asserted to the moment the **first instruction of the ISR (Interrupt Service Routine) executes**.

```
Interrupt Asserted
       │
       ▼
  [Pipeline Flush]
       │
       ▼
  [NVIC Arbitration]
       │
       ▼
  [Hardware Register Stacking]
       │
       ▼
  [ISR Fetch from Memory]
       │
       ▼
  First ISR Instruction Executes   ← Latency ends here
```

### Types of Latency

| Type | Description |
|------|-------------|
| **Hardware Latency** | Fixed cycles for stacking, NVIC arbitration, pipeline flush |
| **Software Latency** | Caused by RTOS masking, long critical sections, priority inversion |
| **Memory Latency** | Flash wait states, cache misses, bus contention |
| **Worst-Case Latency (WCIL)** | Maximum latency under all conditions — critical for hard real-time systems |

### ARM Cortex-M Baseline (Zero Wait-State Memory)

| Event | Cycles |
|-------|--------|
| NVIC arbitration + pipeline flush | ~6 cycles |
| Hardware register stacking (8 regs) | ~12 cycles |
| **Total minimum latency** | **~12–16 cycles** |

---

## 2. Reasons for Interrupt Latency

### 2.1 Hardware Pipeline Flush

- CPU must **complete or abort** the current instruction in the pipeline
- **LDM/STM** (load/store multiple) instructions can be interrupted mid-execution
- Branch misprediction flushes add extra cycles

---

### 2.2 NVIC Arbitration Time

- When **multiple interrupts fire simultaneously**, NVIC selects highest priority
- Arbitration itself consumes cycles
- On Cortex-M: typically **~12 cycles** for exception entry from zero-wait-state memory

---

### 2.3 Hardware Register Stacking (Context Save)

- ARM Cortex-M auto-saves **8 registers** on ISR entry:

```
xPSR, PC, LR, R12, R0, R1, R2, R3
```

- Stacking takes **~12 cycles** on Cortex-M3/M4
- If **FPU is active** (Cortex-M4/M7), lazy stacking may save additional **16–32 FPU registers**, adding significant latency

---

### 2.4 Flash Memory Wait States

- If ISR code sits in **Flash**, the CPU fetches instructions through the flash controller
- Flash wait states (e.g., 3–5 WS at 168 MHz on STM32F4) stall the pipeline on every instruction fetch
- First-time ISR execution is always slower (cold Flash)

---

### 2.5 Cache Miss (Cortex-M7 / High-End MCUs)

- Cortex-M7 has I-Cache and D-Cache
- If ISR code is **not cached**, a cache miss causes a full Flash fetch = many wasted cycles
- Cold-start ISR execution always suffers from this

---

### 2.6 RTOS Priority Masking (Critical Sections)

- `taskENTER_CRITICAL()` in FreeRTOS raises the **BASEPRI** register
- Any ISR with priority numerically **≥ configMAX_SYSCALL_INTERRUPT_PRIORITY** is **masked and deferred**
- ISR stays pending but cannot execute until `taskEXIT_CRITICAL()` is called
- Long critical sections = directly proportional increase in ISR latency

---

### 2.7 Higher-Priority ISR Nesting

- A lower-priority ISR is already executing
- Your ISR must **wait** until the higher-priority one completes
- Deeply nested interrupt chains increase worst-case latency significantly

---

### 2.8 Tail-Chaining Failure

- Cortex-M **tail-chaining** skips full pop+push when back-to-back ISRs fire (saves ~18 cycles)
- If tail-chaining fails (e.g., different priority level triggers full re-stacking):
  - Full pop: 12 cycles + Full push: 12 cycles = **24 wasted cycles**
- With tail-chaining: only **~6 cycles** for transition

---

### 2.9 DMA Bus Contention

- If DMA is actively transferring on the **same bus matrix as the CPU**
- CPU stalls waiting for bus access → ISR instruction fetch is delayed
- Worst during high-bandwidth DMA (ADC continuous mode, SPI bulk transfer)

---

### 2.10 Long-Running Critical Sections in Tasks

- If a task holds `taskENTER_CRITICAL()` and performs heavy work inside it
- Your ISR is **blocked for the entire duration** of that critical section
- A direct software-induced latency contributor

---

### Summary: Latency Sources

| Source | Controllable? |
|--------|---------------|
| Pipeline flush | Partially |
| NVIC arbitration (~12 cycles) | No — hardware fixed |
| Hardware register stacking | Partially (avoid FPU in ISR) |
| Flash wait states | Yes → move ISR to TCM/SRAM |
| Cache miss | Yes → warm cache, use ITCM |
| RTOS priority masking | Yes → set ISR above BASEPRI threshold |
| Higher-priority ISR nesting | Yes → tune priority levels carefully |
| Tail-chain failure | Partially |
| DMA bus contention | Yes → use separate bus masters |
| Long critical sections | Yes → keep critical sections short |

---

## 3. How to Reduce Interrupt Latency

### 3.1 Prioritize Critical ISRs

- Assign **highest priority** to time-sensitive interrupts
- Avoid **priority inversion**
- Keep critical ISRs **above RTOS syscall thresholds**

> **ARM Cortex-M:** Lower numerical value = higher priority. Critical ISR priority must be numerically *lower* than `configMAX_SYSCALL_INTERRUPT_PRIORITY` — making it invisible to `taskENTER_CRITICAL()` masking.

---

### 3.2 Top-Half / Bottom-Half Design

| Half | Role | FreeRTOS Mapping |
|------|------|------------------|
| **Top-Half** | Ultra-fast, essential work only | ISR |
| **Bottom-Half** | Deferred processing | High-priority task via `xTaskNotifyFromISR()`, queue, or semaphore |

```c
// ISR (Top-Half) — just signal the task
void UART_IRQHandler(void) {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xTaskNotifyFromISR(uartTaskHandle, 0, eNoAction, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

// Task (Bottom-Half) — do the real work
void UartTask(void *pvParam) {
    while(1) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        // process data here
    }
}
```

---

### 3.3 Avoid Function Calls in ISRs

- Prefer `static inline` and macros over regular function calls
- Use **direct register access** where possible
- For guaranteed inlining on GCC/ARM:

```c
__attribute__((always_inline)) static inline void clearFlag(void) {
    UART1->SR &= ~UART_SR_RXNE;
}
```

> `static inline` alone does **not** guarantee inlining — the compiler may still emit a call. Use `always_inline` for ISR-critical paths.

---

### 3.4 Place ISR Code in TCM or SRAM

| Memory | Access Speed | Notes |
|--------|-------------|-------|
| Flash (no cache) | 3–5+ wait states | Worst for latency |
| Flash (cached) | 0 if cache hit | Unpredictable cold start |
| SRAM | 1–2 cycles | Better than Flash |
| **TCM** | **Single-cycle** | **Ideal for ISRs** |

**ARM Cortex-M (GCC linker section):**
```c
__attribute__((section(".itcm"))) void UART_IRQHandler(void) { ... }
```

**AURIX TriCore:** Place ISRs in **PSPR** (Program Scratch-Pad RAM) for single-cycle instruction fetch.

---

### 3.5 Avoid Heavy Operations Inside ISRs

| Operation | Reason to Avoid |
|-----------|-----------------|
| `printf` / logging | Blocking, uses heap, slow UART/semihosting |
| `malloc` / dynamic memory | Non-deterministic, fragmentation risk |
| Floating point ops | FPU lazy stacking saves extra registers on Cortex-M4/M7 |
| Large data copies | Wastes CPU cycles; use DMA instead |
| RTOS API calls (non-FromISR) | Will corrupt RTOS state or cause HardFault |

---

### 3.6 Zero-Copy Data Handling

- Use **ring buffers** — ISR writes only an index/pointer, not the data itself
- Use **pre-allocated memory pools** — no runtime allocation
- Consumer task does the actual data processing

```c
// ISR: advance write pointer only — no data copy
ring_buf.data[ring_buf.head] = peripheral->DR;
ring_buf.head = (ring_buf.head + 1) % RING_BUF_SIZE;
```

---

### 3.7 Use DMA for Deterministic Transfers

- ISR triggers **DMA start**
- DMA Transfer Complete (TC) interrupt fires when done
- CPU remains free during the entire transfer

```
ISR (start DMA) ──► DMA runs independently ──► TC ISR (handle completion)
```

> On **AURIX MCAL**: this is exactly how SPI (async job notification) and ADC (DMA result transfer) work in AUTOSAR driver configuration.

---

### 3.8 Minimize ISR Prologue / Epilogue Cost

On ARM Cortex-M, hardware auto-saves 8 registers on ISR entry:
```
xPSR, PC, LR, R12, R0, R1, R2, R3
```

To minimize additional overhead:
- Avoid unnecessary local variables (prevents compiler from saving R4–R11)
- Keep ISR body short — fewer variables = smaller stack frame
- Consider `__attribute__((naked))` for hand-written assembly ISRs where every cycle counts

---

### 3.9 Keep RTOS Critical Sections Short

- Minimize code inside `taskENTER_CRITICAL()` / `taskEXIT_CRITICAL()`
- Never do I/O, memory allocation, or blocking calls inside critical sections
- Every extra cycle in a critical section = direct addition to ISR latency

---

## 4. Complete Summary

```
Interrupt Latency
       │
       ├── What it is
       │       └── Time from interrupt assertion → first ISR instruction
       │
       ├── Causes
       │       ├── Pipeline flush
       │       ├── NVIC arbitration
       │       ├── Hardware stacking (8 regs + FPU lazy stacking)
       │       ├── Flash wait states
       │       ├── Cache miss
       │       ├── RTOS BASEPRI masking
       │       ├── ISR nesting
       │       ├── DMA bus contention
       │       └── Long critical sections
       │
       └── Reduction Techniques
               ├── Priority tuning (above BASEPRI threshold)
               ├── Top-half / Bottom-half design
               ├── Inline / macro register access
               ├── Place ISR in TCM/SRAM
               ├── No printf / malloc / FPU in ISR
               ├── Zero-copy ring buffers
               ├── DMA offload
               ├── Minimize stack frame
               └── Short critical sections
```

---

*Applies to: ARM Cortex-M3/M4/M7, AURIX TriCore TC2xx/TC3xx, FreeRTOS*
