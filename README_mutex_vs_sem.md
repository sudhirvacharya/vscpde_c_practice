# Mutex vs Semaphore — When to Use What

## One-liner

> **Mutex protects a shared resource. Semaphore coordinates activity.**

---

## Decision Rule

Ask yourself one question:

> **Am I protecting a *thing*, or signaling that something *happened*?**

---

## Mutex — Use When Protecting a Shared Resource

**Problem:** One task is using something. Others need to stay out until it's done.

**Key property:** Ownership — the task that locks it must be the one to unlock it.

**Bonus:** Most RTOSes apply **priority inheritance** on mutexes, which prevents priority inversion.

### Use a mutex for:
- Shared peripheral (UART, SPI, CAN TX buffer)
- Driver state machine / global struct
- Shared linked list or queue
- Logging path used by multiple tasks

### Example
```c
xSemaphoreTake(xUartMutex, portMAX_DELAY);
uart_write("data\r\n");
xSemaphoreGive(xUartMutex);
```

---

## Binary Semaphore — Use When Signaling an Event

**Problem:** Something happened. Wake up and handle it.

**Key property:** No ownership — the giver and taker are *different* tasks (or ISR → task).

### Use a binary semaphore for:
- ISR → task notification (ADC done, DMA complete, EXTI fired)
- One task signals another that data is ready
- Any "wake up and process" pattern

### Example
```c
// ISR side
xSemaphoreGiveFromISR(xAdcDoneSem, &xHigherPriorityTaskWoken);
portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

// Task side
xSemaphoreTake(xAdcDoneSem, portMAX_DELAY);
process_sample(adc_read_sample());
```

---

## Counting Semaphore — Use When Managing a Resource Pool

**Problem:** You have N identical resources. Track how many are free.

### Use a counting semaphore for:
- Pool of DMA descriptors or sensor buffers
- Fixed number of worker slots
- Message block pool

### Example
```c
// Producer — grab a free buffer slot
xSemaphoreTake(xFreeBufferSem, portMAX_DELAY);
fill_and_queue(get_free_buffer());

// Consumer — return buffer to pool
process_and_release(buf);
xSemaphoreGive(xFreeBufferSem);
```

---

## Quick Reference Table

| Question | Primitive |
|---|---|
| Protecting one shared resource? | **Mutex** |
| ISR/task signaling an event? | **Binary Semaphore** |
| Tracking a pool of N resources? | **Counting Semaphore** |

---

## Why Not Just Use Binary Semaphore Everywhere?

A binary semaphore *can* gate a critical section, but it has no concept of ownership.

Without ownership → no priority inheritance → **priority inversion risk**.

Classic scenario:
1. Low-prio task locks resource with binary semaphore
2. High-prio task blocks waiting for it
3. Medium-prio task preempts the low-prio task
4. High-prio task is now stuck behind medium-prio — even though medium never touched the resource

With a **mutex**, the RTOS boosts the low-prio task's priority temporarily so it can finish and release the resource sooner.

---

## TL;DR

```
Protecting a shared thing      → mutex
Signaling something happened   → binary semaphore  
Managing a pool of N things    → counting semaphore
```
