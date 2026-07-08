# Linux Kernel and Driver Interview Questions

*Prepared by EmbeddedShiksha (www.embeddedshiksha.com)*

## Process Management
1. How to manipulate the current process states?
2. What are kernel threads?
3. How are threads implemented in the Linux kernel?
4. What are the different states of a process in Linux?
5. What is the difference between a process and a thread?
6. What resources are generally shared between threads?
7. What is a process descriptor?
8. What is task_struct?
9. What is thread_info structure for?
10. What was the need for the thread_info structure?
11. Difference between fork() and vfork()?
12. What is process context?
13. What is a zombie process?
14. How is a parentless process handled in Linux?

## Process Scheduling
1. What is process scheduling?
2. What is cooperative multitasking and pre-emptive multitasking?
3. What is yielding?
4. What is the limitation of cooperative multitasking?
5. I/O bound versus processor bound process?
6. What is process priority?
7. What kind of priority is maintained in Linux?
8. What is nice value?
9. What is virtual run time?
10. What are the available scheduling classes in Linux?
11. Which type of scheduling is used in Linux?
12. How is the next task picked for scheduling?
13. What is the scheduler entry point in Linux?
14. What is a waitqueue?
15. How is context switching handled in Linux?
16. What is user preemption and kernel preemption?

## Syscalls
1. What are syscalls?
2. How are system calls implemented in Linux?
3. What happens when a process in userspace calls a syscall?
4. What is the need for verifying parameters in the definition of a syscall?
5. What is system call context?
6. Why is it not recommended to write new syscalls?

## Interrupt Handling
1. What is an interrupt?
2. What is an interrupt handler or ISR?
3. What are top halves and bottom halves?
4. How is an interrupt registered?
5. What are the different interrupt handler flags?
6. How are interrupts freed?
7. What considerations should be taken care of while writing an interrupt handler?
8. What is interrupt context?
9. How to disable and enable interrupts?
10. What are the different bottom half techniques in Linux?
11. What are tasklets, softirqs, and workqueues, and the difference among them?
12. When to choose which bottom half?
13. How to implement softirqs, tasklets, and workqueues?
14. How to schedule a tasklet?
15. What is ksoftirqd?
16. How to disable bottom halves?
17. How is locking between bottom halves handled?

## Kernel Synchronization
1. What is synchronization?
2. What is a critical section?
3. What is a race condition?
4. Why do we need to take care of synchronization?
5. What are the various synchronization techniques in Linux?
6. What is a deadlock?
7. What is an atomic operation?
8. What is a spinlock?
9. What is a reader-writer spin lock?
10. What is a semaphore?
11. What is a binary semaphore?
12. What is the difference between semaphore and spinlock?
13. When to choose between spinlock and semaphore?
14. What is the difference between semaphore and mutex?
15. What is preemption disabling and what is its use?

## Memory Management
1. How is memory managed in Linux?
2. What are pages?
3. What are the different memory zones in Linux?
4. How to allocate pages?
5. How to free pages?
6. What is kmalloc, and what are its action modifiers?
7. What is a zone modifier in Linux?
8. What is vmalloc?

## Virtual File System
1. What is the virtual file system, and what is the need for it in Linux?
2. What are the different object types in VFS?
3. What operations are possible on inode and superblock objects?

## Process Address Space
1. What is process address space?
2. What is the memory descriptor in Linux, and which structure represents it?
3. How to allocate and destroy a memory descriptor?
4. Does a kernel thread have any association with mm_struct?
5. What is a VMA, and what VMA operations are possible in the Linux kernel?
6. How to manipulate a memory area in Linux?
7. What is mmap and do_mmap()?
8. What is a page table?

## Device Driver Questions
1. What is a device driver, and what is the need for it?
2. What are the different kinds of devices?
3. What is a module in Linux?
4. How are modules loaded in Linux?
5. Difference between insmod and modprobe?
6. How are parameters shared between driver modules?
7. What are IOCTLs?
8. What are syscalls?
9. What are the benefits of syscalls?
10. How is a character driver registered in Linux?
11. What are the init and exit functions of a driver?
12. How and when are the init and exit functions of a driver called?
13. What is a probe function?
14. When is probe called?
15. What is a platform device?
16. What is a device tree?
17. What are the benefits of a device tree over board files?
18. What are sysfs and procfs?
19. How are logs printed in the Linux kernel, and what are the log levels?
20. What are copy_to_user and copy_from_user?
21. What do you mean by kernel configuration, and what are the ways of configuring the kernel?
22. What is menuconfig?
23. What is ioremap?
24. What is a segmentation fault?
25. What are the various ways of debugging the Linux kernel?
26. How does the Linux kernel boot?
27. What are zImage and bzImage?
28. What are the different boot arguments in Linux?
29. How are parameters passed from the bootloader to the kernel?
30. What is ATAGs?
31. From which file does kernel execution start?
32. What is a bootloader?
33. What are primary and secondary bootloaders?
34. Why do we need two bootloaders?
35. Difference between poll and select?
36. What is priority inheritance and priority inversion?
37. What are the different types of kernel?
38. What is DMA?
39. What is cache coherency?
40. What is copy-on-write?
41. What are highmem and lowmem?
42. What happens if we pass an invalid address from userspace using ioctl?
43. What are the different IPC mechanisms in Linux?
44. What are sockets?
45. How is a page fault handled in Linux?
46. Difference between memory-mapped IO and port-mapped IO?
47. What are I2C and SPI?
48. How does physical-to-virtual translation work in Linux?
49. What are thrashing, segmentation, and fragmentation?
50. What is preempt_count, and what is its need?

# Linux Kernel and Driver Interview Questions
### Deep-Dive Answer Guide — 15 Years Embedded/Linux Driver Experience

*Prepared by Datta Tak | Embedded Enthusiast | Automotive Platform Software | Linux Kernel | AUTOSAR | Device Drivers*
*[linkedin.com/in/dattatak](https://www.linkedin.com/in/dattatak)*

---

## How to Use This Guide

Do not memorize definitions only. In interviews for Staff/Senior Staff Linux kernel roles, the interviewer expects three levels: **concept clarity, kernel execution path, and production failure handling**. For every answer, try to explain: what kernel object is involved, what lock/context rules apply, what can go wrong on real hardware, and how you debug it.

- Use the first line of each answer as the crisp interview answer.
- Use the field-proven/corner-case lines when the interviewer asks: *have you seen this in real life?*
- For driver questions, always mention context: process context, interrupt context, atomic context, sleepable context, DMA/cache context.
- For automotive and SoC platforms, connect the answer to boot time, suspend/resume, watchdog reset, IRQ storm, DMA coherency, data corruption, and race conditions.

---

## 1. Process Management

A Linux process is represented by `task_struct`. Threads are also tasks; they share selected resources through CLONE flags. In driver work, process management matters when you block in `read()`, `poll()`, `ioctl()`, wait queues, kernel threads, and signal handling.

### 1.1 How do you manipulate current process state?
Use `set_current_state()`, `__set_current_state()`, `schedule()`, `wake_up*()`, and `wait_event*()` primitives. The common pattern: set state to `TASK_INTERRUPTIBLE`/`TASK_UNINTERRUPTIBLE`, place the task on a wait queue, test the condition, call `schedule()`, wake it when the condition becomes true. Modern code prefers `wait_event_interruptible()` because it handles the repeated condition check safely.

- **Field-proven:** Never set `TASK_INTERRUPTIBLE` and forget to call `schedule()` or restore `TASK_RUNNING` — causes strange latency and missed wake-up behavior.
- **Corner case:** Lost wake-up occurs when the condition changes before the task actually sleeps. Always protect condition and wait queue sequencing.
- **Example:** A character driver `read()` waits until RX FIFO has data; ISR pushes bytes and calls `wake_up_interruptible()`.

### 1.2 What are kernel threads and how are threads implemented in Linux?
A kernel thread is a schedulable task executing only in kernel address space, created via `kthread_run()` or `kthread_create()+wake_up_process()`. User threads/processes are `task_struct`; a thread shares `mm_struct`, `files_struct`, signal handlers, etc. with its thread group depending on clone flags.

- **Field-proven:** Use kernel threads for long-running sleepable background work, not hard IRQ handling. For short deferred jobs, workqueues are usually better.
- **Corner case:** Kernel threads generally have no user `mm_struct`. Accessing user pointers from a kthread is wrong unless explicitly attached to an mm.
- **Example:** A camera driver may use a kthread to dequeue completed frames and notify V4L2 buffers.

### 1.3 What states can a process be in?
`TASK_RUNNING`, `TASK_INTERRUPTIBLE`, `TASK_UNINTERRUPTIBLE`, `TASK_KILLABLE`, `TASK_STOPPED`, `TASK_TRACED`, `EXIT_ZOMBIE`, `EXIT_DEAD`. `TASK_RUNNING` = executing or ready to run. `TASK_INTERRUPTIBLE` can be woken by a signal; `TASK_UNINTERRUPTIBLE` is used when the wait must not be interrupted (e.g. certain IO paths).

- **Field-proven:** Many production hangs are tasks stuck in D state — usually uninterruptible sleep waiting for IO, lock, hardware completion, or filesystem response.
- **Corner case:** Too much `TASK_UNINTERRUPTIBLE` makes shutdown/recovery painful since signals cannot abort the wait.
- **Example:** `cat /proc/<pid>/status` or `sysrq-t` shows state and stack trace.

### 1.4 Difference between process and thread?
A process has its own virtual address space, file descriptor table and resource ownership. A thread is a schedulable execution context inside a process, typically sharing address space, open files, signal handlers and working directory with sibling threads. In Linux both are `task_struct` entries; the difference is resource sharing.

- **Field-proven:** Linux has no separate kernel object called "thread" — it has tasks created with clone flags.
- **Corner case:** A bug in one thread can corrupt shared address space and crash the entire process.
- **Example:** `pthread_create()` eventually maps to `clone()` with flags such as `CLONE_VM` and `CLONE_FILES`.

### 1.5 What is process descriptor, task_struct and thread_info?
`task_struct` is the main process descriptor — scheduling info, state, PID, credentials, signal state, mm pointer, files pointer, parent/children relation, and architecture-specific fields. `thread_info` historically stored low-level per-thread data near the kernel stack; on many modern architectures it has been reduced/moved for security and robustness.

- **Field-proven:** Never assume old textbook layout of `thread_info` at bottom of stack on all modern kernels.
- **Corner case:** Kernel stack overflow historically could corrupt `thread_info` — one reason newer designs separated sensitive data from stack-adjacent memory.
- **Example:** The `current` macro returns the current `task_struct`, implemented architecture-dependently.

### 1.6 fork() vs vfork()?
`fork()` creates a child using copy-on-write page tables so parent and child run independently. `vfork()` creates a child that shares the address space temporarily; the parent is suspended until the child calls `execve()` or `_exit()`. `vfork()` exists for performance but is dangerous if the child modifies memory or returns from the function.

- **Field-proven:** Prefer `posix_spawn()` or `fork()+exec` unless you fully understand vfork restrictions.
- **Corner case:** Calling `printf()`, `malloc()`, or returning from a function in a vfork child can corrupt the parent process.
- **Example:** Boot-time init systems may optimize process creation, but correctness matters more than micro-optimization.

### 1.7 What is process context?
Kernel code executing on behalf of a process: `current` is valid, may sleep if not in an atomic section, can access user memory safely via `copy_to_user`/`copy_from_user`, and can be preempted depending on kernel configuration. Driver file operations like open/read/write/ioctl usually run in process context.

- **Field-proven:** Before taking a mutex or doing blocking IO, ask: am I in process context or interrupt context?
- **Corner case:** A function can run in process context but still be atomic if a spinlock is held or preemption/interrupts are disabled.
- **Example:** `ioctl()` path can sleep; ISR cannot sleep.

### 1.8 Zombie and parentless process handling?
A zombie is a terminated child whose exit status hasn't been collected by the parent via `wait()`. If a process becomes parentless, it's reparented to init/systemd or a subreaper, which later collects it.

- **Field-proven:** Zombies don't consume CPU, but too many consume PID/table resources and indicate a parent wait logic bug.
- **Corner case:** In containers, PID namespace subreaper behavior changes who adopts orphan processes.
- **Example:** `ps` shows Z state; fix the parent to handle `SIGCHLD` and `waitpid()`.

---

## 2. Process Scheduling

Scheduling selects the next runnable task on each CPU. Linux supports fair, real-time, deadline and idle classes. Driver engineers care because wrong locking or IRQ design can cause latency spikes, missed audio/camera deadlines, watchdog bites and priority inversion.

### 2.1 What is process scheduling? Cooperative vs preemptive multitasking?
Scheduling is the kernel decision of which runnable task executes on a CPU. Cooperative multitasking relies on tasks voluntarily yielding; preemptive multitasking allows the kernel timer interrupt, wake-up path or preemption logic to switch tasks even if the running task didn't yield.

- **Field-proven:** Linux is preemptive, but exact preemption behavior depends on `PREEMPT_NONE`, `VOLUNTARY`, `PREEMPT`, `PREEMPT_RT` and `preempt_count`.
- **Corner case:** A CPU-bound kernel loop with preemption disabled can still hurt latency even on a preemptive kernel.
- **Example:** A driver busy-waiting for hardware for 20 ms can starve real-time audio.

### 2.2 What is yielding and its limitation?
`yield()` tells the scheduler the current task is willing to let others run. Rarely a good synchronization method — proper design uses wait queues, completions, mutexes, semaphores, blocking IO or poll mechanisms.

- **Field-proven:** yield is not a timing guarantee and often hides bad design.
- **Corner case:** Using yield in a loop can burn CPU while still not ensuring the desired task runs.
- **Example:** Replace `while(!ready) yield();` with `wait_event_interruptible(queue, ready);`

### 2.3 IO-bound versus CPU-bound process?
An IO-bound task sleeps often waiting for disk/network/device IO; a CPU-bound task uses CPU continuously. CFS naturally gives interactive/IO-bound tasks good response because their virtual runtime advances slowly while sleeping.

- **Field-proven:** In embedded systems, a camera/audio thread may look IO-bound but can still be deadline-sensitive.
- **Corner case:** A thread waiting for a device IRQ may miss latency if IRQ affinity or CPU isolation is misconfigured.
- **Example:** Audio capture has periodic wakeups; CPU-bound logging thread must not run on an isolated real-time core.

### 2.4 What is process priority, nice value and virtual runtime?
Normal tasks use nice values -20 to +19 (lower = higher weight). CFS tracks virtual runtime, growing faster for low-priority tasks and slower for high-priority tasks. The scheduler selects the runnable entity with smallest virtual runtime.

- **Field-proven:** Don't say Linux only uses fixed priority — CFS uses weighted fair scheduling for normal tasks.
- **Corner case:** Real-time classes `SCHED_FIFO`/`SCHED_RR` can starve CFS tasks if misused.
- **Example:** A logging process set to `SCHED_FIFO` can accidentally starve system services.

### 2.5 What scheduling classes are available?
Common classes: stop, deadline, real-time, fair, idle. `SCHED_DEADLINE` uses runtime/deadline/period parameters. `SCHED_FIFO`/`SCHED_RR` are real-time classes. `SCHED_NORMAL`/`BATCH`/`IDLE` are fair-class policies.

- **Field-proven:** Class order matters — higher scheduling class is considered before lower class.
- **Corner case:** `PREEMPT_RT` changes many spinlocks into sleeping locks and affects latency behavior.
- **Example:** Use `SCHED_FIFO` carefully for hard periodic threads; always budget CPU and watchdog recovery.

### 2.6 How is next task picked and what is scheduler entry point?
`schedule()` is the central entry into the scheduler; `pick_next_task()` consults scheduling classes in priority order. For CFS, tasks are organized by virtual runtime in a red-black tree; the leftmost/min-vruntime task is preferred.

- **Field-proven:** The wake-up path can preempt the current task if the new task should run earlier.
- **Corner case:** On SMP, load balancing, CPU affinity, cpuset, IRQ affinity and energy-aware scheduling all influence where tasks run.
- **Example:** QNX/RTOS interviews often compare explicit core affinity; Linux can migrate tasks unless pinned.

### 2.7 What is a waitqueue?
A kernel mechanism for putting tasks to sleep until a condition becomes true. Widely used in drivers for blocking read/write, poll, hardware completion, resource availability.

- **Field-proven:** Always wait on a condition, not just an event. Wakeups can be spurious or arrive before sleep.
- **Corner case:** Forgetting `wake_up()` after changing condition causes permanent block. Waking before condition update causes a race.
- **Example:** `wait_event_interruptible(wq, rx_count > 0)` in read(); ISR increments `rx_count` and calls `wake_up_interruptible(&wq)`.

### 2.8 How is context switching handled? User preemption vs kernel preemption?
A context switch saves current task CPU state, switches address space if needed, updates scheduler accounting, switches kernel stack and resumes the next task. User preemption happens when returning to user mode if `need_resched` is set. Kernel preemption allows switching while executing kernel code if `preempt_count` is zero and the kernel is configured for preemption.

- **Field-proven:** Locks and interrupt-disabled regions increase `preempt_count` and block preemption.
- **Corner case:** A latency bug may be caused by long preempt-disabled sections, not high CPU load.
- **Example:** Use ftrace/`preemptoff`/`irqsoff` tracers to prove max latency source.

---

## 3. System Calls

System calls are controlled entry points from user space to kernel space. Driver developers touch syscalls indirectly through file operations, ioctl, mmap, poll and read/write paths.

### 3.1 What is a system call and how is it implemented?
A kernel service invoked by user space using an architecture-specific trap instruction (`syscall`, `svc`, `ecall`). The CPU switches privilege level, enters the syscall entry path, validates arguments, calls the `sys_*` implementation, returns a result or negative errno, then returns to user mode.

- **Field-proven:** System calls are ABI; once exposed, they're hard to change. New syscalls are discouraged unless there's a strong generic need.
- **Corner case:** Never directly dereference user pointers in a syscall or driver file operation — use `copy_from_user`/`copy_to_user` or `get_user`/`put_user`.
- **Example:** `read(fd, buf, len)` enters kernel, VFS resolves `file_operations->read_iter`, driver copies data to the user buffer.

### 3.2 What happens when user space calls a syscall?
Registers hold the syscall number and arguments. CPU enters kernel mode, saves user context, checks tracing/seccomp/audit hooks, dispatches to the syscall table, executes kernel code, stores the return value, checks pending signals and rescheduling, then returns to user space.

- **Field-proven:** The syscall path is security-critical — validate size, pointer, permission, object lifetime and integer overflow.
- **Corner case:** A 32-bit user process on a 64-bit kernel needs compat syscall handling for structures with different layouts.
- **Example:** An ioctl structure with pointer-size fields must support `compat_ioctl` if 32-bit apps run on a 64-bit kernel.

### 3.3 What is system call context?
Process context. `current` points to the calling task, sleeping is allowed unless a lock/atomic section prevents it, and user memory access is possible via safe helpers. Faults can occur while copying user memory.

- **Field-proven:** `copy_from_user` can sleep because it may fault in user pages. Do not call it under a spinlock.
- **Corner case:** If the user passes an invalid address, `copy_from_user` fails and the driver should return `-EFAULT`, not crash.
- **Example:** In ioctl, validate command, size, direction, user pointer and permission before touching hardware.

### 3.4 Why avoid adding new syscalls?
New syscalls create permanent ABI, require architecture table updates, audit/seccomp/libc support and long-term compatibility. For device-specific operations, use existing interfaces: ioctl, netlink, configfs/sysfs, char devices, or subsystem-specific APIs.

- **Field-proven:** For Linux upstream, an ioctl may be rejected if it duplicates existing subsystem patterns.
- **Corner case:** Don't use sysfs for high-frequency data plane; use read/write/mmap/ioctl/poll as appropriate.
- **Example:** Sensor configuration can use sysfs attributes; streaming frames should use V4L2, not custom syscalls.

---

## 4. Interrupt Handling and Bottom Halves

Interrupt design decides latency, data loss and system stability. A good driver does minimum work in hard IRQ, acknowledges hardware, captures state, and defers heavy work to a suitable bottom half.

### 4.1 What is interrupt, ISR, top half and bottom half?
An interrupt is a hardware/software event that diverts CPU execution to a handler. The top half is the hard IRQ handler registered by `request_irq()` — must be fast and non-sleeping. Bottom halves defer work to softirq, tasklet, threaded IRQ or workqueue depending on latency and sleep requirements.

- **Field-proven:** Never do heavy parsing, blocking I2C/SPI transfer or `GFP_KERNEL` memory allocation inside hard IRQ.
- **Corner case:** On shared IRQ lines, the handler must check device interrupt status and return `IRQ_NONE` if not its interrupt.
- **Example:** Ethernet ISR acknowledges DMA interrupt and schedules NAPI poll; packet processing is deferred.

### 4.2 How is interrupt registered and freed? What flags matter?
Use `request_irq()` or `devm_request_irq()` to register, `free_irq()` or devm-managed cleanup to release. Important flags: `IRQF_SHARED`, `IRQF_TRIGGER_RISING/FALLING/HIGH/LOW`, `IRQF_ONESHOT`, `IRQF_NO_THREAD`. Threaded handlers use `request_threaded_irq()`.

- **Field-proven:** Prefer `devm_request_irq()` in platform drivers to simplify probe error paths.
- **Corner case:** Wrong trigger type from device tree can create missing interrupts or interrupt storms.
- **Example:** GPIO interrupt configured level-low but hardware leaves line low → endless IRQ storm.

### 4.3 What should you consider while writing interrupt handlers?
Keep it short, acknowledge/clear the hardware cause correctly, avoid sleeping, avoid unbounded loops, protect shared data with irq-safe locks, handle spurious/shared IRQs, use correct memory barriers for MMIO, and defer heavy work.

- **Field-proven:** Clearing interrupt before reading status can lose edge events on some hardware — follow TRM ordering.
- **Corner case:** If the device requires read-to-clear, logging or extra reads can accidentally clear status.
- **Example:** For UART RX, drain FIFO within a safe bound and push data to tty flip buffer or schedule work.

### 4.4 What is interrupt context and how to enable/disable interrupts?
Interrupt context has no process backing for sleeping, cannot block, and must use atomic-safe APIs. Disable local interrupts with `local_irq_disable()`/`local_irq_save()`, re-enable with `local_irq_enable()`/`local_irq_restore()`. For shared data with an IRQ handler, use `spin_lock_irqsave()`.

- **Field-proven:** `local_irq_disable` affects only the current CPU, not all CPUs. Use proper locking for SMP.
- **Corner case:** Disabling interrupts too long causes latency, missed deadlines and watchdog resets.
- **Example:** Protect a register shadow updated by both ioctl and ISR using `spin_lock_irqsave` in process context and `spin_lock` in IRQ if IRQ is already disabled.

### 4.5 Softirq, tasklet, workqueue and ksoftirqd — difference?
Softirqs are high-performance deferred work used by networking/block layers and can run concurrently on multiple CPUs. Tasklets are built on softirq and historically serialize per tasklet but are less favored in newer code. Workqueues run in process context and may sleep. `ksoftirqd` is a per-CPU kernel thread that processes softirqs when overloaded or deferred from interrupt return.

- **Field-proven:** Use workqueue if you need to sleep; use threaded IRQ if the work is tightly tied to an interrupt but may sleep.
- **Corner case:** Softirq overload can move processing to `ksoftirqd`, increasing latency and causing packet drops.
- **Example:** Network RX uses NAPI polling to limit interrupt storms and shift work into controlled softirq context.

### 4.6 When to choose bottom-half technique?
Hard IRQ for minimal acknowledge/capture. Threaded IRQ when interrupt handling may sleep or needs priority control. Workqueue for sleepable, longer jobs. Softirq/NAPI for high-throughput networking. Avoid new tasklet usage where modern alternatives exist.

- **Field-proven:** In upstream review, the bottom-half choice must match context and subsystem conventions.
- **Corner case:** Workqueue for very high-rate packet path adds scheduling overhead; softirq for sleepable I2C transaction will break.
- **Example:** Touchscreen IRQ can use threaded IRQ to read coordinates over I2C.

### 4.7 How is locking between bottom halves handled?
Use `spin_lock_bh()` when shared data is accessed from process context and softirq/bottom-half context on the same CPU. Use `spin_lock_irqsave()` if a hard IRQ can access it. Use mutex only when all users are sleepable process context.

- **Field-proven:** Pick the lock based on the most restrictive context that touches the data.
- **Corner case:** Taking a mutex in softirq/hardirq causes a sleep-in-atomic bug.
- **Example:** A network driver protects TX ring indices shared with NAPI using spin locks and NAPI rules.

---

## 5. Kernel Synchronization

Synchronization prevents races when multiple CPUs, tasks, interrupts or bottom halves access shared data. Correct primitive choice depends on context, sleepability, hold time and priority requirements.

### 5.1 What is synchronization, critical section and race condition?
Synchronization coordinates access to shared resources. A critical section must execute atomically with respect to other users. A race condition occurs when final behavior depends on uncontrolled timing between execution contexts.

- **Field-proven:** A race is not always reproducible — prove with locking audit, ftrace, lockdep, KCSAN or stress tests.
- **Corner case:** A race may disappear when `printk` is added because timing changes.
- **Example:** ISR updates `rx_head` while `read()` updates `rx_tail`; missing lock corrupts the ring buffer.

### 5.2 What are Linux synchronization techniques?
`atomic_t`/`refcount_t`, spinlock, rwlock, seqlock, mutex, semaphore, completion, wait queue, RCU, percpu variables, bit locks and memory barriers. There's no single best primitive — context decides.

- **Field-proven:** Use `refcount_t` instead of `atomic_t` for object lifetime when possible — it catches overflow misuse.
- **Corner case:** Memory barriers are required when ordering matters across CPUs or device MMIO; locks imply many CPU ordering guarantees but not always device ordering.
- **Example:** Use completion to wait for firmware load done, not a polling loop.

### 5.3 What is deadlock?
Execution contexts wait forever due to circular dependency, unreleased lock, lock inversion, or sleeping while holding a resource needed by the wake-up path. Prevention: lock ordering, timeouts, lockdep, error-path cleanup, avoiding blocking calls under locks.

- **Field-proven:** Most production deadlocks are error-path bugs — return without unlock, or a callback re-entering the same lock.
- **Corner case:** ABBA deadlock across two locks may appear only under heavy SMP stress.
- **Example:** Thread A holds `bus_lock` waiting for `pm_lock`; suspend path holds `pm_lock` waiting for `bus_lock`.

### 5.4 What is atomic operation?
An operation completing indivisibly with respect to other CPUs. Linux provides `atomic_t`, `atomic64_t`, bit operations and `refcount_t`. Good for counters/flags, not for protecting complex structures.

- **Field-proven:** Atomic does not automatically make a multi-field structure consistent.
- **Corner case:** `atomic_read` followed by `atomic_inc` is not one atomic transaction unless using a compare/exchange loop.
- **Example:** Use `atomic_t open_count` for simple exclusive open; use mutex for a state machine.

### 5.5 What is spinlock and reader-writer spinlock?
A spinlock busy-waits until the lock is available and must be held briefly. Safe in atomic context; IRQ variants can protect data shared with interrupt handlers. Reader-writer spinlocks allow multiple readers or one writer but can be harmful with writer starvation or added complexity.

- **Field-proven:** Never sleep while holding a spinlock. Keep register updates short.
- **Corner case:** On `PREEMPT_RT`, many spinlocks become sleeping rtmutexes except `raw_spinlock` — understand RT behavior.
- **Example:** Use `spin_lock_irqsave` around a hardware FIFO index shared between ISR and ioctl.

### 5.6 Semaphore vs spinlock vs mutex?
Spinlock: short atomic sections, cannot sleep. Mutex: mutual exclusion in process context, can sleep, has ownership and priority inheritance on RT. Semaphore: counting sleepable primitive, lacks strict ownership; binary semaphores are older style, often replaced by mutex/completion.

- **Field-proven:** Mutex for protecting one resource, completion for one-time event, semaphore for resource count.
- **Corner case:** A mutex cannot be released by a different task; a semaphore can be upped by another context — can hide design bugs.
- **Example:** SPI bus access from file operations uses mutex; ISR completion uses `complete()`.

### 5.7 When to choose spinlock or semaphore/mutex?
Spinlock if the code can run in IRQ/softirq/atomic context or must not sleep and hold time is tiny. Mutex/semaphore if the code may sleep, hold time may be longer, or it calls I2C/SPI/regulator/clk APIs that may sleep.

- **Field-proven:** Read the call graph — if any called API can sleep, spinlock is wrong.
- **Corner case:** `kmalloc(GFP_KERNEL)` under spinlock can sleep. Use `GFP_ATOMIC` or move allocation outside the lock.
- **Example:** In `probe()`, use mutex for configuration; in ISR, use spinlock for status flags.

### 5.8 What is preemption disabling?
`preempt_disable()` prevents kernel preemption on the current CPU. Used for per-CPU data access or very short critical sections. Does not disable interrupts and does not protect against other CPUs.

- **Field-proven:** `preempt_disable` is not a replacement for a spinlock on SMP shared data.
- **Corner case:** A long preempt-disabled region causes scheduling latency and missed real-time deadlines.
- **Example:** Access `this_cpu_ptr` safely in a preemption-disabled region.

---

## 6. Memory Management and Address Space

For drivers, the most important decisions are kmalloc vs vmalloc, GFP flags, DMA-safe memory, mmap, and user pointer safety.

### 6.1 How is memory managed in Linux? What are pages and zones?
Linux manages physical memory in pages (commonly 4 KB, architecture-dependent). The buddy allocator manages page blocks by order. Slab/slub allocators build small object caches on top. Zones such as DMA, DMA32, Normal, HighMem and Movable represent physical constraints and allocation policies.

- **Field-proven:** Drivers must respect DMA address limitations — a 32-bit DMA engine cannot access arbitrary high physical memory without IOMMU or bounce buffering.
- **Corner case:** Allocating large physically contiguous memory late after boot can fail due to fragmentation.
- **Example:** Use CMA or `dma_alloc_coherent` for camera/video buffers needing DMA-safe memory.

### 6.2 How to allocate and free pages?
Use `alloc_pages()`, `__get_free_pages()`, `get_zeroed_page()` and `free_pages()`/`__free_pages()` for page-level allocation. For small kernel memory, use `kmalloc`/`kfree`. For virtually contiguous but not physically contiguous large memory, use `vmalloc`/`vfree`.

- **Field-proven:** Do not use vmalloc memory for DMA unless specifically mapped for DMA — physical pages are not contiguous.
- **Corner case:** High-order `alloc_pages` may fail under memory pressure even if total free memory looks enough.
- **Example:** A driver allocating an order-8 buffer after the system runs for hours may fail; reserve memory at boot or use CMA.

### 6.3 What is kmalloc and GFP/action modifiers?
`kmalloc` allocates physically contiguous memory suitable for many DMA-capable cases when mapped appropriately. `GFP_KERNEL` may sleep and is used in process context. `GFP_ATOMIC` is for atomic/IRQ context, used sparingly. Flags like `__GFP_ZERO` and zone modifiers influence allocation behavior.

- **Field-proven:** The allocation flag must match context — wrong flag causes sleep-in-atomic or allocation failure.
- **Corner case:** `GFP_ATOMIC` allocations are limited; repeated large atomic allocations cause intermittent failures.
- **Example:** Allocate RX descriptors during probe, not in every ISR.

### 6.4 What is vmalloc?
Allocates virtually contiguous memory backed by non-contiguous physical pages. Useful for large kernel buffers not used directly by DMA. Higher overhead and different mapping behavior than kmalloc.

- **Field-proven:** Use vmalloc for large software tables; avoid it for hot paths and direct DMA.
- **Corner case:** Some functions expect physically contiguous memory and will fail or corrupt if a vmalloc pointer is used.
- **Example:** A debug trace buffer can use vmalloc; a DMA descriptor ring should not.

### 6.5 What is process address space, mm_struct and VMA?
Process address space is a process's virtual memory layout. `mm_struct` describes it. `vm_area_struct` represents a continuous region such as code, heap, stack, shared library mapping or device mmap. VMAs store permissions, flags and operations such as fault handling.

- **Field-proven:** Kernel threads usually have no private user mm — they borrow `active_mm` for scheduling mechanics.
- **Corner case:** Accessing `current->mm` in a kthread can be NULL — design kthreads to avoid user memory.
- **Example:** `/proc/<pid>/maps` shows VMAs.

### 6.6 How to allocate/destroy memory descriptor?
Normal process creation duplicates or creates `mm_struct` through fork/exec internals (`dup_mm`, `mm_alloc`), and releases through `mmput`/`exit_mmap`. Driver code rarely allocates `mm_struct` manually — it interacts through mmap, `get_user_pages` or `copy_*_user` APIs.

- **Field-proven:** Know the concept, but do not create `mm_struct` in drivers.
- **Corner case:** Pinning user pages with `get_user_pages` can break COW/lifetime assumptions if not released correctly.
- **Example:** Zero-copy DMA to user buffers requires careful pinning, DMA mapping and unpinning.

### 6.7 What is mmap and do_mmap()?
mmap maps files, anonymous memory, or device memory into process address space. In drivers, `file_operations->mmap` maps device buffers or MMIO using `remap_pfn_range`, `dma_mmap_coherent` or `vm_insert_page` depending on memory type. `do_mmap` is an internal kernel path used to create mappings.

- **Field-proven:** Mapping device registers to user space is dangerous — validate permissions and cache attributes.
- **Corner case:** Wrong cache attribute on a mmaped DMA buffer causes stale frames or data corruption.
- **Example:** V4L2 maps camera capture buffers to user space for zero-copy access.

### 6.8 What is page table and page fault handling?
Page tables translate virtual addresses to physical frames with permissions and attributes. A page fault occurs when translation is missing or permission fails. The kernel fault handler checks VMA, permissions and fault type, loads pages, handles COW, grows the stack, or sends SIGSEGV if invalid.

- **Field-proven:** Not every page fault is an error — demand paging and COW are normal.
- **Corner case:** A page fault in atomic context is fatal if the code cannot sleep or recover.
- **Example:** `copy_from_user` may fault and sleep to bring a user page into memory.

### 6.9 What are highmem/lowmem, COW, thrashing, segmentation and fragmentation?
Lowmem is permanently mapped kernel-accessible memory on older 32-bit systems; highmem requires temporary mapping. Copy-on-write shares physical pages until one writer modifies. Thrashing is excessive paging causing poor progress. Segmentation is logical memory division; fragmentation is free memory split into unusable chunks.

- **Field-proven:** On modern 64-bit SoCs, highmem is less visible, but fragmentation and DMA constraints remain real.
- **Corner case:** A system can have enough free memory but fail a large contiguous allocation due to fragmentation.
- **Example:** CMA reserves contiguous memory for multimedia/DMA drivers.

---

## 7. VFS and Driver File Operations

VFS provides a common abstraction over filesystems and device nodes. Character drivers expose `file_operations` so user space can open/read/write/ioctl/poll/mmap them.

### 7.1 What is VFS and why is it needed?
The Virtual File System is the kernel abstraction layer that provides common file APIs independent of the actual filesystem or device implementation. Lets `read()`, `write()`, `open()`, `poll()`, `mmap()` and `ioctl()` work uniformly on files, pipes, sockets and device nodes.

- **Field-proven:** For drivers, VFS is the bridge between a user-space file descriptor and kernel driver callbacks.
- **Corner case:** Incorrect `file_operations` lifetime during module unload can crash if an open file still references removed code.
- **Example:** `/dev/myadc` is a character device file but VFS dispatches operations to the driver.

### 7.2 VFS object types and inode/superblock operations?
Key objects: `super_block` (mounted filesystem), `inode` (file metadata), `dentry` (directory cache/name lookup), `file` (an opened instance), `address_space` (page cache). `super_operations` manage filesystem-level behavior; `inode_operations` manage lookup/create/link; `file_operations` manage open/read/write/ioctl/mmap/poll.

- **Field-proven:** Interviews expect the inode vs file distinction — inode represents the object, file represents the open instance.
- **Corner case:** Private data should usually be stored in `file->private_data` per open, not globally.
- **Example:** `open()` allocates per-client context and stores it in `file->private_data`; `release()` frees it.

### 7.3 What are poll and select?
Allow user space to wait until file descriptors become readable, writable or exceptional. The driver's poll callback registers wait queues with `poll_wait()` and returns a readiness mask such as `POLLIN`/`POLLOUT`.

- **Field-proven:** poll must not sleep forever — it should register a wait queue and return current readiness.
- **Corner case:** If the driver forgets `wake_up` when state changes, epoll/select users block forever.
- **Example:** UART driver wakes poll waiters when RX data arrives.

---

## 8. Device Drivers, Device Tree and Kernel Modules

Driver questions are the heart of embedded Linux interviews. The strong answer connects Linux device model, bus matching, probe/remove, resources, clocks, regulators, pinctrl, interrupts, MMIO, DMA, userspace ABI and debug strategy.

### 8.1 What is a device driver and what kinds of devices exist?
Kernel code that controls hardware and exposes it through standard kernel subsystems or user APIs. Common classes: character, block and network devices, plus subsystem-specific drivers for I2C, SPI, GPIO, PWM, IIO, V4L2, ALSA, DRM, PCIe and platform devices.

- **Field-proven:** Good upstream drivers integrate with existing subsystems instead of exposing random custom char-device APIs.
- **Corner case:** A driver that works in bring-up may fail upstream review if it bypasses framework conventions.
- **Example:** ADC should usually use IIO; camera sensor uses V4L2 subdevice; audio codec uses ASoC.

### 8.2 What is a kernel module? How is it loaded? insmod vs modprobe?
A module is loadable kernel object code. `insmod` inserts a specific `.ko` file without resolving dependencies. `modprobe` uses `modules.dep`, aliases and configuration to load dependencies automatically. `rmmod` removes modules when the reference count permits.

- **Field-proven:** In production, module autoload often happens through udev/modalias matching.
- **Corner case:** Module unload can fail if the device file is open or a subsystem holds references.
- **Example:** `modprobe i2c-dev` also loads dependencies; `insmod` may fail with unknown symbols.

### 8.3 How are parameters shared between driver modules?
Module parameters for boot/load-time configuration, exported symbols for internal kernel APIs, device tree/ACPI for hardware description, platform data in legacy systems, and subsystem interfaces. Avoid hidden global coupling between unrelated modules.

- **Field-proven:** For board-specific hardware values, device tree is better than module parameters.
- **Corner case:** `module_param` is not a stable user ABI for complex runtime control.
- **Example:** GPIO number, IRQ trigger and regulator names should come from device tree.

### 8.4 What are IOCTLs and how to design them?
ioctl provides device-specific commands beyond read/write. Use `_IO`, `_IOR`, `_IOW`, `_IOWR` macros, fixed-size structures, versioning/reserved fields, permission checks and `compat_ioctl` for 32-bit user space on 64-bit kernels.

- **Field-proven:** Never trust ioctl input — validate command number, size, direction, pointer, ranges and state.
- **Corner case:** Changing structure layout breaks ABI. Add reserved fields from day one.
- **Example:** A DSP driver ioctl loads firmware, starts stream, queries status and maps buffers.

### 8.5 How is character driver registered?
Allocate device numbers with `alloc_chrdev_region`, initialize cdev with `cdev_init`, add with `cdev_add`, create class/device for `/dev` node, and implement `file_operations`. Many modern drivers use `misc_register` for simple misc char devices.

- **Field-proven:** Handle every error path in reverse order: `cdev_del`, `unregister_chrdev_region`, `device_destroy`, `class_destroy`.
- **Corner case:** If cdev is added before the object is fully initialized, user space can open it and race the probe.
- **Example:** Initialize locks, wait queues and hardware state before `device_create` exposes the `/dev` node.

### 8.6 What are init, exit, probe and remove?
`module_init` runs when the module loads; `module_exit` runs when unloaded. `probe` is called by the bus/device model when a matching device is found. `remove` runs when the device is removed or the driver unbound. Probe should acquire resources, initialize hardware, register interfaces and set driver data.

- **Field-proven:** Probe can be deferred with `-EPROBE_DEFER` if a dependency such as regulator/clock/GPIO isn't ready.
- **Corner case:** Probe order changes across boots — never rely on fixed driver load order.
- **Example:** A display driver defers probe until panel regulator and clock providers are available.

### 8.7 What is platform device and device tree?
A platform device represents non-discoverable SoC hardware described by firmware/board data. Device tree is a hardware description passed to the kernel, containing compatible strings, register ranges, interrupts, clocks, regulators, GPIOs, pinctrl and child nodes. The driver matches using the compatible string and obtains resources from DT.

- **Field-proven:** Device tree describes hardware, not Linux policy — don't put random driver behavior knobs unless the binding allows.
- **Corner case:** Wrong reg size or interrupt specifier causes silent MMIO fault or no interrupt.
- **Example:** `compatible = "vendor,my-uart"; reg = <0x12340000 0x1000>; interrupts = <GIC_SPI 45 IRQ_TYPE_LEVEL_HIGH>;`

### 8.8 Device tree benefits over board files?
DT separates hardware description from kernel C board files, enabling one kernel image to support multiple boards, improving maintainability, reviewability and bootloader/kernel handoff. It also standardizes resource discovery.

- **Field-proven:** Bindings are ABI — once accepted, maintain compatibility.
- **Corner case:** DT cannot fix bad hardware sequencing alone — the driver must still handle reset/clock/regulator order.
- **Example:** The same UART driver supports many SoC variants through compatible data.

### 8.9 sysfs vs procfs?
sysfs exposes structured kernel object attributes (usually one value per file), tied to the device model. procfs exposes process and kernel runtime information. New driver control/status attributes usually belong in sysfs, debugfs or subsystem APIs, not arbitrary procfs.

- **Field-proven:** Don't expose high-frequency data through sysfs — it's a configuration/status plane, not a streaming data plane.
- **Corner case:** sysfs ABI is considered stable; poorly designed attributes become a long-term burden.
- **Example:** Expose firmware version in sysfs; stream sensor samples via IIO buffer.

### 8.10 Kernel logs and log levels?
Use `pr_err`, `pr_warn`, `pr_info`, `pr_debug`, `dev_err`, `dev_warn`, `dev_info` and `dev_dbg`. `dev_*` is preferred in drivers because it includes device context. Log levels: emergency, alert, critical, error, warning, notice, info, debug.

- **Field-proven:** Don't flood logs in ISR or hot path — use rate-limited variants.
- **Corner case:** `printk` can change timing and mask races; dynamic debug is better for controlled debug.
- **Example:** `dev_err_probe(dev, ret, "failed to get regulator\n")` handles probe defer logs cleanly.

### 8.11 copy_to_user/copy_from_user?
Safely copy data between kernel and user space, returning the number of bytes not copied. Drivers should return `-EFAULT` on failure. May sleep due to page faults, so don't use under spinlock or in interrupt context.

- **Field-proven:** Always copy user data into a kernel structure first, validate, then use.
- **Corner case:** TOCTOU risk — user can change memory after validation if you repeatedly access the user pointer.
- **Example:** ioctl: `copy_from_user(&kcmd, uarg, sizeof(kcmd));` validate `kcmd`; perform operation; `copy_to_user` result.

### 8.12 Kernel configuration and menuconfig?
Kernel config controls which features/drivers are built-in, modular or disabled. Interfaces: `make menuconfig`, `nconfig`, `xconfig`, `oldconfig`, `defconfig`, `savedefconfig` and fragments used by build systems. Kconfig expresses dependencies and selections.

- **Field-proven:** A driver may not probe because a dependency config is missing, not because the code is wrong.
- **Corner case:** Built-in driver timing differs from module load timing — probe deferral becomes important.
- **Example:** `CONFIG_I2C`, `CONFIG_REGMAP`, `CONFIG_OF` and subsystem configs may be required.

### 8.13 What is ioremap and MMIO?
`ioremap` maps physical device register addresses into kernel virtual address space with appropriate device memory attributes. Access should use `readl`/`writel` or relaxed variants with correct barriers. For platform drivers, `devm_ioremap_resource` maps the resource safely.

- **Field-proven:** Never dereference a physical register address directly on MMU systems.
- **Corner case:** Using a normal cached mapping for MMIO causes incorrect register behavior.
- **Example:** `res = platform_get_resource(pdev, IORESOURCE_MEM, 0); base = devm_ioremap_resource(dev, res);`

### 8.14 What is segmentation fault?
User-space process termination due to invalid memory access, protection violation or unmapped address. In the kernel, the equivalent is an oops/panic depending on severity; the kernel must not blindly trust user pointers.

- **Field-proven:** A driver bug can cause a user segfault by returning bad mmap or corrupting a user buffer length.
- **Corner case:** SIGBUS can occur for mmaped device/file access beyond valid backing, not only SIGSEGV.
- **Example:** User maps a device buffer, then the driver frees backing memory incorrectly; later access crashes.

### 8.15 Kernel debugging methods?
`dmesg`, dynamic debug, ftrace, tracepoints, perf, eBPF, lockdep, KASAN/KCSAN/KMSAN, kmemleak, crash dumps, pstore/ramoops, kgdb, JTAG, sysrq, `/proc/interrupts`, `/proc/lockdep`, debugfs and subsystem tools.

- **Field-proven:** A senior debug flow starts with reproduction, timestamps, kernel log, stack traces, IRQ counts, locks, memory, and hardware register dump.
- **Corner case:** Adding printk in hot paths changes timing — use tracepoints/ftrace for lower disturbance.
- **Example:** For intermittent DMA corruption: enable DMA API debug, add cache sync trace, check IOMMU faults and compare physical addresses.

---

## 9. Boot Flow, Images and Boot Arguments

Boot questions test architecture-level understanding: ROM, bootloader stages, kernel decompression, device tree, initramfs, rootfs and the first userspace process.

### 9.1 How does Linux kernel boot and from which file does execution start?
Boot ROM loads the first bootloader, which initializes minimal hardware and loads a later bootloader/kernel. The bootloader loads the kernel image, DTB and initramfs, sets boot arguments and jumps to the kernel entry. Architecture-specific head code starts first, sets up MMU/page tables, decompresses the kernel if needed, then `start_kernel` initializes core kernel subsystems and eventually runs init.

- **Field-proven:** Exact entry file is architecture-dependent — for ARM64, entry code is under `arch/arm64/kernel/head.S` before C `start_kernel`.
- **Corner case:** Early kernel panic can be due to wrong load address, DTB mismatch, memory map, console bootarg or decompression issue.
- **Example:** `earlycon` and `initcall_debug` help debug early boot.

### 9.2 zImage vs bzImage?
zImage is a compressed kernel image commonly associated with ARM and older flows. bzImage is the x86 big zImage format supporting larger compressed kernels. Modern ARM64 commonly uses Image or Image.gz depending on the bootloader.

- **Field-proven:** Do not generalize image names across architectures — answer per architecture.
- **Corner case:** Bootloader must know whether the image is compressed and where to place DTB/initramfs.
- **Example:** U-Boot `booti` boots ARM64 Image, `bootz` boots zImage, `bootm` boots uImage/FIT.

### 9.3 Boot arguments and passing parameters from bootloader?
Kernel command-line parameters passed by the bootloader via device tree chosen/bootargs, EFI stub, ATAGs on older ARM, or architecture-specific protocols. Configure console, rootfs, loglevel, earlycon, init, memory, module params and debugging options.

- **Field-proven:** A wrong console bootarg can make a good boot look dead because logs go elsewhere.
- **Corner case:** `mem=` or `cma=` bootargs can hide memory and break DMA buffer allocation.
- **Example:** `console=ttyS0,115200 earlycon root=/dev/mmcblk0p2 rw initcall_debug`.

### 9.4 What are ATAGs?
Older ARM boot parameter structures used to pass memory, command line and initrd information from bootloader to kernel. Device tree replaced ATAGs in modern ARM Linux.

- **Field-proven:** Mention ATAGs for legacy ARM; for new systems focus on DTB/ACPI/EFI.
- **Corner case:** A legacy bootloader may pass an incomplete ATAG memory map causing early boot failure.
- **Example:** Migrating old board files to DT often removes ATAG dependency.

### 9.5 Primary vs secondary bootloader and why two bootloaders?
The primary bootloader is loaded by ROM from fixed boot media and initializes minimal resources. The secondary bootloader has more features: DDR init, storage/network/filesystem, secure boot checks, DTB selection and kernel loading. Multiple stages exist due to ROM size limits, security chain and hardware initialization complexity.

- **Field-proven:** In automotive SoCs, the secure boot chain and safety boot manager may add more stages.
- **Corner case:** If DDR training is unstable, kernel failures look random but the root cause is an earlier bootloader stage.
- **Example:** ROM → SPL → U-Boot → Linux kernel → init.

---

## 10. Advanced Driver Topics: DMA, Cache, IPC, Sockets and Realtime Bugs

These questions separate textbook knowledge from board-level debugging experience. DMA and cache coherency are frequent root causes of intermittent field failures.

### 10.1 What is DMA?
DMA allows a device to transfer data to/from memory without the CPU copying each byte. The CPU programs descriptors/registers, maps buffers for device access, starts hardware, and receives a completion interrupt. Linux uses DMA mapping APIs to handle cache and IOMMU details.

- **Field-proven:** Always use `dma_map_single`/`dma_unmap_single` or `dma_alloc_coherent` depending on streaming vs coherent design.
- **Corner case:** Using `virt_to_phys` on normal memory for DMA is a classic bug on IOMMU/non-linear mapping systems.
- **Example:** Camera CSI writes frames to DMA buffers; CPU only handles buffer queue and completion.

### 10.2 What is cache coherency?
CPU cache and device-visible memory agree about the latest data. Some systems are hardware coherent; others require explicit cache clean/invalidate via DMA APIs. For `DMA_TO_DEVICE`, CPU data must be cleaned before the device reads. For `DMA_FROM_DEVICE`, CPU cache must be invalidated before the CPU reads device-written data.

- **Field-proven:** Never manually guess cache maintenance if the Linux DMA API can do it.
- **Corner case:** A bug may show only at high frame rate or on one CPU because stale cache lines are timing-sensitive.
- **Example:** Audio buffer has old samples because the driver forgot `dma_sync_single_for_cpu` before reading captured data.

### 10.3 What is priority inversion and inheritance?
Priority inversion occurs when a high-priority task waits on a lock held by a low-priority task while medium-priority tasks run, delaying the low-priority lock release. Priority inheritance temporarily boosts the lock owner's priority to reduce inversion. Linux RT mutexes support PI; `PREEMPT_RT` relies heavily on this.

- **Field-proven:** In driver design, avoid holding a mutex across slow IO if a high-priority thread depends on it.
- **Corner case:** Spinlocks do not solve long resource blocking — they may worsen latency.
- **Example:** Audio real-time thread blocked on a control mutex held by a low-priority userspace configuration task.

### 10.4 What are IPC mechanisms and sockets?
Linux IPC includes pipes, FIFO, signals, shared memory, message queues, semaphores, futexes, eventfd, signalfd, netlink, Unix domain sockets and TCP/UDP sockets. Sockets provide an endpoint abstraction for communication between processes or machines.

- **Field-proven:** Kernel-to-user event notification often uses a pollable char device, netlink, uevent or eventfd depending on subsystem.
- **Corner case:** Signals are poor for high-rate data; shared memory needs synchronization.
- **Example:** A driver sends a hotplug event through uevent; high-rate telemetry uses mmap ring + poll.

### 10.5 Memory-based IO vs port-based IO?
Memory-mapped IO maps device registers into address space and uses load/store style access via `readl`/`writel`. Port-mapped IO uses a separate IO address space and `inb`/`outb` instructions, mainly x86 legacy. ARM/SoC devices are usually MMIO.

- **Field-proven:** Use the correct accessor — do not use raw pointer dereference for MMIO.
- **Corner case:** Endian and barrier requirements differ across devices.
- **Example:** PCI device BAR may be ioremaped and accessed with `readl`/`writel`.

### 10.6 What are I2C and SPI?
I2C is a two-wire address-based bus with open-drain lines, ACK/NACK, relatively low speed. SPI is a full-duplex synchronous bus with chip select, clock, MOSI and MISO — typically faster but more pins and no standard addressing. Linux provides subsystem APIs for both.

- **Field-proven:** Do not access I2C/SPI from hard IRQ because transfers can sleep.
- **Corner case:** I2C bus stuck low needs recovery pulses; SPI first-byte corruption often comes from CS timing, mode or DMA cache issues.
- **Example:** Touch controller interrupt wakes a threaded IRQ which performs an I2C read.

### 10.7 Physical to virtual translation in Linux?
CPU MMU translates virtual addresses through page tables to physical addresses. The kernel direct map maps much of physical RAM into kernel virtual space. `ioremap` maps device physical addresses. DMA addresses may differ from CPU physical addresses when an IOMMU is active.

- **Field-proven:** Virtual, physical and DMA addresses are not always interchangeable.
- **Corner case:** Printing a kernel virtual pointer and programming it into a DMA register is wrong.
- **Example:** Use the `dma_handle` returned by `dma_alloc_coherent` for the device register, not the CPU pointer.

### 10.8 What is preempt_count and why needed?
`preempt_count` tracks nesting of preemption-disabled regions, softirq/hardirq/NMI context and related atomic state. It tells the kernel whether preemption is allowed and helps detect sleeping in atomic context.

- **Field-proven:** When you see "BUG: sleeping function called from invalid context", `preempt_count` tells you what atomic context was active.
- **Corner case:** A function may run in process context but have `preempt_count` nonzero because a spinlock is held.
- **Example:** `copy_to_user` under `spin_lock` triggers a sleeping-in-atomic warning.

---

## 11. Real-Time Debug Playbook for Linux Driver Interviews

Use this chapter to answer scenario-based questions. Interviewers often ask: driver probes but does not work, IRQ storm, DMA corruption, device hangs after suspend, boot hang, or random watchdog reset.

### Scenario 1: Driver probe fails intermittently with -EPROBE_DEFER.
Check dependency readiness: clocks, regulators, GPIO expanders, pinctrl, PHYs, reset controllers and parent buses. Use `dev_err_probe` so defer is not logged as a hard error. Verify device tree phandles and provider drivers are enabled and registered.

- **Field-proven:** Probe order is not deterministic. Correct design must tolerate dependency deferral.
- **Corner case:** A missing CONFIG for a provider driver looks the same as a dependency never arriving.
- **Example:** I2C sensor defers until the regulator driver probes; without regulator config it never succeeds.

### Scenario 2: Interrupt storm after enabling device.
Confirm IRQ trigger type, status/clear sequence, level vs edge behavior, shared IRQ status check, device clock/reset state and pinctrl. Check `/proc/interrupts` counts. Read hardware status before and after clearing. Use `disable_irq_nosync` temporarily only as containment.

- **Field-proven:** Most IRQ storms are wrong trigger polarity, unacknowledged level interrupt, or device status not cleared due to missing clock.
- **Corner case:** Clearing status may require write-1-to-clear — writing 0 does nothing.
- **Example:** GPIO line configured falling-edge while the device outputs level-low until the FIFO drained.

### Scenario 3: DMA buffer has stale or corrupted data.
Audit DMA mapping direction, cache sync points, buffer alignment, IOMMU mapping, device address width, descriptor ownership bits, memory barriers and lifetime. Use DMA API debug and compare CPU pointer vs DMA handle usage.

- **Field-proven:** On non-coherent SoCs, a cache maintenance bug may pass on one board and fail on another.
- **Corner case:** CPU touches the buffer after `dma_map_single(DMA_TO_DEVICE)` before the device completes — data becomes inconsistent.
- **Example:** For RX, call `dma_sync_single_for_cpu` before parsing a packet, then `dma_sync_single_for_device` before returning the buffer to hardware.

### Scenario 4: System hangs in D state during driver read().
Dump task stacks with `sysrq-t`, identify wait queue/completion/lock, verify wake_up/complete path, IRQ firing, hardware status and timeout handling. Replace infinite waits with timeout where recovery is possible.

- **Field-proven:** Production drivers should not wait forever for hardware. Use bounded timeout and a reset path.
- **Corner case:** If IRQ is disabled or missed, completion never arrives and the user process becomes unkillable if `TASK_UNINTERRUPTIBLE`.
- **Example:** `wait_for_completion_timeout(&done, msecs_to_jiffies(100))` then reset the controller and return `-ETIMEDOUT`.

### Scenario 5: Suspend/resume breaks device.
Check runtime PM/system PM callbacks, clock/regulator/reset sequencing, IRQ wake settings, pinctrl sleep/default states, DMA quiesce, pending work cancellation and register context restore. Ensure no userspace file operation races with the suspend path.

- **Field-proven:** Many resume failures are missing register reprogramming after a power domain is turned off.
- **Corner case:** A workqueue running after suspend begins can access powered-off registers.
- **Example:** `pm_runtime_get_sync` before MMIO access and `pm_runtime_put_autosuspend` after the operation.

### Scenario 6: Kernel oops in driver remove/unload.
Check object lifetime: unregister user-visible interfaces before freeing memory, synchronize IRQ/work/timer/kthread, disable hardware, free DMA, and only then release core structures. Use devm carefully — devm does not automatically solve asynchronous user references.

- **Field-proven:** Expose last, remove first. Stop new users before freeing existing resources.
- **Corner case:** A work item queued before remove runs after memory is freed — use `cancel_work_sync`.
- **Example:** remove: `device_destroy` → `cdev_del` → `disable_irq` → `cancel_work_sync` → `kthread_stop` → free buffers.

---

## Final Interview Golden Rules

- Always mention execution context before selecting API: process, interrupt, softirq, atomic, sleepable.
- Use Linux framework APIs: DMA API, device-managed resources, regmap, clk/regulator/pinctrl, subsystem APIs.
- Never trust user input. Validate pointers, sizes, command IDs, permissions and state.
- In hard IRQ: acknowledge, capture, defer. Do not sleep.
- For DMA: CPU pointer is not device address. Use DMA handle and mapping APIs.
- For locking: choose primitive based on context and hold time. Never sleep under a spinlock.
- For probe: initialize completely before exposing user API. In remove: stop users before freeing resources.
- For production: every wait needs a timeout or a clear reason why it cannot time out.
- For interview: explain the failure you saw, how you proved it, and what permanent fix you made.

> **One-line senior answer:** Linux driver development is not about calling APIs; it is about respecting context, lifetime, synchronization, memory attributes and hardware sequencing under real-world timing.
