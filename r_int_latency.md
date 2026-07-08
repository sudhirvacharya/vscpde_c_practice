# Interrupt Latency: Definitions & Minimization Techniques

## Definitions

- **Interrupt Latency** — the time delay between the moment a hardware device raises an interrupt request and the moment the processor begins executing the corresponding ISR (Interrupt Service Routine).
- **Interrupt Servicing Time** — the time taken to actually service/complete the interrupt once the ISR starts running (distinct from latency).

## 1. Hardware Selection
- Choose microcontrollers with **dedicated hardware interrupt vectors** — lets the processor jump straight to the ISR without extra lookup/delay.

## 2. Use an RTOS
- An RTOS enforces strict scheduling rules for tasks and interrupts, giving more **predictable, deterministic** response times.

## 3. Interrupt Configuration
- **Proper Prioritization** — clearly define interrupt priorities so the most critical signals get serviced first.
- **Enable Nested Interrupts** — allow higher-priority interrupts to preempt an ongoing lower-priority ISR, reducing worst-case latency.

## 4. Coding Practices
- **Minimize Critical Sections** — keep interrupt-disabled code blocks as short as possible so the system stays responsive to new requests.
- **Design Efficient/Short ISRs** — do only the essential work (e.g., acknowledge hardware, capture data) in the ISR itself; defer heavier processing to a background task/thread (e.g., via PendSV or a task queue).
- **Use DMA** — offload heavy data transfers to Direct Memory Access, bypassing the CPU/interrupt path entirely for bulk data movement.

## 5. Priority Assignment
- Assign the **highest priority** to time-critical interrupts.
- Ensure lower-priority ISRs are kept short so they don't block higher-priority ones for long.

## 6. Hardware/CPU Power States
- **Disable power-saving features** (C-States, SpeedStep, etc.) in BIOS/firmware — prevents cores from entering sleep states that add wake-up latency when an interrupt arrives.

## 7. OS-Level (Linux specific)
- **Use the PREEMPT_RT patch** — converts the Linux kernel to a fully preemptible kernel, giving constant/deterministic preemption and interrupt-handling latency instead of best-effort scheduling.

---

## Quick Summary Table

| Technique | Why it helps |
|---|---|
| Dedicated HW vectors | Skips vector-lookup delay |
| RTOS | Deterministic scheduling |
| Priority + nesting | Critical interrupts serviced first, can preempt |
| Short critical sections | Less time interrupts stay masked |
| Lean ISR + deferred work | Reduces time spent in interrupt context |
| DMA | Removes CPU from data-path entirely |
| Disable C-States | No wake-latency from sleep states |
| PREEMPT_RT (Linux) | Deterministic kernel preemption |
