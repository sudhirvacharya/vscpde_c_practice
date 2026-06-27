# Watchdog Timer Refresh Placement — Interview Challenge

## Problem Faced

During an interview embedded systems task, I configured a **Watchdog Timer (WDT)** refresh (kick) inside a **high-priority task**. The system appeared to run, but the WDT was **never actually resetting** the device when it should have — the watchdog wasn't catching fault conditions as intended.

Root cause discovered later: **the refresh was placed in the wrong task priority level.**

---

## What I Configured (Wrong)

```c
// ❌ WRONG — WDT kick in high-priority task
void vHighPriorityTask(void *pvParameters) {
    while (1) {
        do_critical_work();
        HAL_IWDG_Refresh(&hiwdg);  // Kick here — BAD
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}
```

### Why This Failed

The high-priority task **always gets CPU time first** in a preemptive RTOS scheduler. Even when lower-priority tasks were starved or stuck, the high-priority task kept running and kept kicking the WDT.

```
High-pri task  ████████████████████████  ← always runs, always kicks WDT
Low-pri task   ░░░░░░░░░░░░░░░░░░░░░░░░  ← starved, stuck, but WDT doesn't care
Idle           ░░░░░░░░░░░░░░░░░░░░░░░░
```

Result: **WDT never fired** even when the system was in a degraded state.

---

## Root Cause

| Factor | Detail |
|--------|--------|
| High-priority task | Scheduled first, runs reliably |
| WDT kick in high-pri | As long as this one task is alive, WDT stays happy |
| Lower task failures | Deadlocks, starvation, missed deadlines — all invisible to WDT |
| Expected behavior | WDT should catch *any* task failure, not just high-pri |

---

## Correct Fix

### Option 1 — Kick in Idle Task (Simple)

```c
// ✅ Kick in idle — only runs when ALL tasks have yielded
void vApplicationIdleHook(void) {
    HAL_IWDG_Refresh(&hiwdg);
}
```

Idle task runs **only when no other task needs CPU**. If any task is stuck/spinning without yielding, idle never runs → WDT fires → system resets. ✅

```
High-pri task  ████░░░░████░░░░████░░░░
Low-pri task   ░░░░██░░░░░░██░░░░░░██░░
Idle           ░░░░░░██░░░░░░██░░░░░░██  ← WDT kick here only
```

### Option 2 — Bitmask Supervisor (Robust, Production-Grade)

```c
// Each task registers a bit
#define TASK_ADC_BIT   (1 << 0)
#define TASK_CAN_BIT   (1 << 1)
#define TASK_UART_BIT  (1 << 2)
#define ALL_TASKS_MASK (TASK_ADC_BIT | TASK_CAN_BIT | TASK_UART_BIT)

volatile uint32_t wdt_checkin_flags = 0;

// Each task sets its bit when healthy
void vADCTask(void *p) {
    while (1) {
        do_adc_work();
        wdt_checkin_flags |= TASK_ADC_BIT;  // Check in
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

// Supervisor task kicks WDT only when ALL tasks checked in
void vWDTSupervisor(void *p) {
    while (1) {
        if ((wdt_checkin_flags & ALL_TASKS_MASK) == ALL_TASKS_MASK) {
            wdt_checkin_flags = 0;           // Reset flags
            HAL_IWDG_Refresh(&hiwdg);        // Kick only if all healthy
        }
        // If any task missed check-in: no kick → WDT fires → reset
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
```

---

## Key Lesson

> **The WDT refresh location determines what the watchdog actually monitors.**

| Placement | Catches | Misses |
|-----------|---------|--------|
| High-priority task | High-pri task crash only | All lower task failures |
| Idle task | Any task stuck without yielding | High-pri task spinning (still yields idle eventually) |
| Bitmask supervisor | Per-task health individually | Nothing — most complete coverage |

---

## Takeaway for RTOS/Embedded Design

- Never kick the WDT unconditionally in a single high-priority task
- Prefer idle hook for simple liveness detection
- Use bitmask supervisor pattern for safety-critical or AUTOSAR-style systems where every task's health must be independently verified
- The watchdog is only as good as where you place the kick — a misplaced kick gives false confidence

---

*Challenge encountered during embedded systems RTOS interview — STM32/FreeRTOS context*
