# Critical Section in Synchronization

A critical section is a segment of code where a process or thread accesses shared resources—such as memory locations, data structures, or files. To prevent corrupted data and race conditions, operating systems ensure that only one process can execute within its critical section at any given time.

---

## Structure of a Critical Section

A typical critical section sequence is divided into four main parts:

1. **Entry Section** — The code segment where a process requests permission to enter its critical section.
2. **Critical Section** — The actual part of the code where the process accesses or modifies the shared resource.
3. **Exit Section** — The code segment that follows the critical section, which "releases" the resource so other processes can access it.
4. **Remainder Section** — The rest of the program code where no shared resources are accessed.

---

## Requirements for a Valid Solution

To safely manage access to shared resources and avoid the *Critical Section Problem*, any synchronization mechanism must satisfy three core conditions:

| Condition | Description |
|---|---|
| **Mutual Exclusion** | Only one process can be inside the critical section at any given time. If another process attempts to enter, it must wait. |
| **Progress** | If no process is currently executing in its critical section and others are waiting, the decision of which process enters next cannot be postponed indefinitely. |
| **Bounded Waiting** | There must be a strict limit on how many times other processes can enter their critical sections after a process has made a request, preventing starvation. |

> **Progress vs Bounded Waiting (interview tip):**
> - **Progress** = *liveness* — the system keeps moving forward.
> - **Bounded Waiting** = *fairness* — no single thread is starved indefinitely.
> A solution can satisfy Progress but still starve a specific thread if it keeps losing the scheduling lottery.

---

## How Operating Systems Solve It

To enforce mutual exclusion, operating systems utilize hardware-based atomic instructions and software synchronization tools:

### Mutexes (Mutual Exclusion Objects)
- Locks that allow a process to enter a critical section and block others until the lock is released.
- Have **ownership** — only the thread that locked it can unlock it.
- Support **priority inheritance** to prevent priority inversion.
- Best for protecting shared data in task-to-task scenarios.

### Semaphores
- Integer variables accessed via atomic `Wait` (P) and `Signal` (V) operations.
- **Binary semaphore** ≈ mutex in behavior, but **without ownership semantics**.
- **Counting semaphore** tracks N available resources (producer-consumer).
- Preferred for **ISR → Task signaling** since ISRs cannot own a mutex.

### Monitors
- High-level synchronization constructs.
- Ensure only one process can execute active code within the monitor at a time.
- Protect shared data from concurrent access automatically.

### Hardware Atomic Instructions
- `LDEX` / `STEX` (Load/Store Exclusive) on ARM Cortex-M — basis for all mutex implementations.
- `TEST-AND-SET`, `COMPARE-AND-SWAP (CAS)` — classic primitives.
- `CMPSWAP` on AURIX TriCore — atomic compare-and-swap instruction.

---

## Mutex vs Semaphore for Critical Sections

| Property | Mutex | Binary Semaphore |
|---|---|---|
| Ownership | ✅ Yes | ❌ No |
| Priority inheritance | ✅ Supported | ❌ Not supported |
| Accidental release by other task | ❌ Prevented | ✅ Possible (bug risk) |
| Recursive locking | ✅ Supported (recursive mutex) | ❌ Deadlocks |
| ISR-safe posting | ❌ No | ✅ Yes (`xSemaphoreGiveFromISR()`) |
| Use case | Critical section (shared data) | Signaling between tasks/ISR |

**Rule of thumb:**
- **Critical section protecting shared data** → **Mutex**
- **ISR signaling a task** → **Binary Semaphore**
- **Counting available resources** → **Counting Semaphore**

---

## Embedded / RTOS Context

In embedded systems, the "entry section" may mean:
- `xSemaphoreTake()` / `osMutexAcquire()` in FreeRTOS / CMSIS-RTOS
- `GetResource()` / `ReleaseResource()` in AUTOSAR OSEK (uses priority ceiling protocol)
- `__disable_irq()` / `__enable_irq()` on bare-metal for very short ISR-shared data sections

> **AUTOSAR note:** `GetResource()` implements the **Immediate Priority Ceiling Protocol (IPCP)**, raising the task's priority to the ceiling of all tasks sharing that resource — eliminating priority inversion without needing priority inheritance.
