### Sempahore
in rtos, a semaphore is a syxbronization mechanism used to manage access to shared resource and cororinates task. 
semaphore helps prevent issues like race condtion and deadlock in multi tasking 
enviranioment by ensuring that only a specified number of task can access a resource at time.

exammple:
 Parking Lot with N slots Multiple people can enter (up to N slots).  ANY person can signal (release a slot). When slots = 0, everyone WAITS.

### Mutexes:
    in rtos and multithreadifn environment, a mutex is asyncornization mecanism that prevent multiple task or thread from acess that same shared reosurce at asame trime/
    how mutex works:
    a mutex act like lock.a task must aquire the lock the mutex before access the shared resoucre.
    once the a task finsihed using the resoucrece, it release(unlcok) the mutx allowing other task to acess it.
    if another task tries to aquire the mutex while its locked, it has to wait untill the mutex is relases
Example:
Toilet with 1 key 🚽, Only 1 person can enter at a time. The SAME person who locked must unlock.

### Difference between mutex and semaphore?

    Feature              Mutex                         Semaphore
    ----------------     --------------------------    ----------------------
    Ownership            Owned by locking task         No ownership
    Priority inversion   Protected                     Not protected
    Use case             Mutual exclusion (shared data) Signaling

    xSemaphoreTake(mutex, portMAX_DELAY);
    sharedBuffer[0] = 42;   // critical section
    xSemaphoreGive(mutex);

### Difference between a Process and a thread?

    Process (one program running)
    │
    ├── Shared: heap, globals, code, file descriptors
    │
    ├── Thread 1 → own stack, PC, registers
    ├── Thread 2 → own stack, PC, registers
    └── Thread 3 → own stack, PC, registers

### What is priority inversion? How is it solved?

    Scenario:
    - Low-priority task holds mutex
    - High-priority task needs that mutex -- blocks
    - Medium-priority task runs instead (doesn't need mutex)
    - High-priority task effectively runs at low priority

    Solution: Priority Inheritance
    - Temporarily boost low-priority task to match high-priority waiter
    - FreeRTOS mutexes support this automatically

    preempts : higher-priority task immediately interrupts and takes over the CPU from a lower-priority task.

    Timeline:

    L  = Low  priority task   (holds mutex)
    M  = Mid  priority task   (CPU hog)
    H  = High priority task   (waiting for mutex)

    Time ──────────────────────────────────────────────►

    L runs, takes mutex
    │
    └── H wakes up, preempts L, tries to take mutex → BLOCKED
                    │
                    └── M wakes up, preempts L (H is blocked)
                        M runs forever...
                        H is stuck waiting — even though H > L > M
                                ▲
                                └── THIS is priority inversion


###  What is a deadlock? How to avoid it?

    Task A holds Mutex1, waits for Mutex2.
    Task B holds Mutex2, waits for Mutex1.
    Both block forever --> deadlock.

    Prevention:
    - Always acquire mutexes in the SAME ORDER across all tasks
    - Use timeouts instead of blocking forever
    - Minimize number of mutexes held at the same time

## what is my Linux OS Road map

| Phase   | File             | Concepts                                  |
|---------|------------------|-------------------------------------------|
| Phase 1 | `lo_mutex.c`     | Mutex, threads, race conditions           |
| Phase 1 | `lo_semaphore.c` | Semaphore, shared memory, fork            |
| Phase 1 | `lo_process.c`   | fork, wait, waitpid, execvp, exit         |
| Phase 1 | `lo_threads.c`   | pthread_create, join, exit, return values |
| Phase 1 | `lo_sharedmem.c` | mmap, sem_init, shared structures         |
| Phase 2 | `lo_pipe.c`      | Pipes with fork                           |
| Phase 2 | `lo_fifo.c`      | Named pipes (FIFO)                        |
| Phase 2 | `lo_msqueue.c`   | Message queues                            |
| Phase 2 | `lo_socket.c`    | Sockets (do this last)                    |
| Phase 3 | `lo_malloc.c`    | malloc/free internals                     |
| Phase 3 | `lo_stack_heap.c`| Stack vs Heap                             |
| Phase 3 | `lo_mmap.c`      | Memory-mapped files                       |
| Phase 4 | `lo_fileio.c`    | File I/O (open, read, write, close)       |
| Phase 4 | `lo_dirops.c`    | Directory operations                      |
| Phase 4 | `lo_filestat.c`  | File metadata (stat)                      |
| Phase 5 | `lo_signals.c`   | Signal basics                             |
| Phase 5 | `lo_sigaction.c` | sigaction, custom handlers                |
| Phase 6 | `lo_prodcons.c`  | Producer–Consumer problem                 |
| Phase 6 | `lo_readwrite.c` | Readers–Writers problem                   |
| Phase 6 | `lo_deadlock.c`  | Deadlock detection                        |
| Phase 6 | `lo_dining.c`    | Dining Philosophers problem               |