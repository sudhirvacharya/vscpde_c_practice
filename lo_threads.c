/*
 * ============================================================
 * FILE    : lo_threads.c
 * TOPIC   : Linux OS — Thread Management (POSIX Threads)
 * AUTHOR  : sudhirvacharya
 * ============================================================
 *
 * WHAT IS A THREAD?
 * ─────────────────
 * Thread = lightweight unit of execution INSIDE a process
 * Process = factory 🏭
 * Thread  = worker inside factory 👷
 * All threads SHARE the same memory (heap, globals)
 * Each thread has its OWN stack
 *
 * COVERS:
 *   1. pthread_create()   — create a thread
 *   2. pthread_join()     — wait for thread to finish
 *   3. pthread_self()     — get my own thread ID
 *   4. pthread_exit()     — exit from thread
 *   5. pass argument      — send data INTO thread
 *   6. return value       — get data BACK from thread
 *   7. multiple threads   — array of threads in loop
 *
 * ============================================================
 * COMPILE:
 *   gcc -o lo_threads lo_threads.c -lpthread
 *
 * RUN:
 *   ./lo_threads
 *
 * NOTE: -lpthread flag is MANDATORY for pthread functions
 * ============================================================
 *
 * MENTAL MODEL:
 *
 *   main() [Manager 👔]
 *       │
 *       ├── pthread_create ──→ Thread 1 [Worker 👷]
 *       ├── pthread_create ──→ Thread 2 [Worker 👷]
 *       ├── pthread_create ──→ Thread 3 [Worker 👷]
 *       │
 *       └── pthread_join × 3 ──→ wait for all workers
 *
 * ============================================================
 *
 * THREAD vs PROCESS COMPARISON:
 * ──────────────────────────────────────────────────────
 *  Process (lo_process.c)  │  Thread (lo_threads.c)
 * ──────────────────────────────────────────────────────
 *  fork()                  │  pthread_create()
 *  wait()                  │  pthread_join()
 *  exit()                  │  pthread_exit()
 *  getpid()                │  pthread_self()
 *  separate memory         │  shared memory
 *  heavyweight             │  lightweight
 *  created by OS           │  created inside process
 * ──────────────────────────────────────────────────────
 *
 * ============================================================
 * EXPECTED OUTPUT:
 * ============================================================
 *
 * ========================================
 *   lo_threads.c — Thread Management
 * ========================================
 * MAIN  : Main thread ID = 139785234567890
 *
 * ===== DEMO 1: Basic Thread =====
 * MAIN  : Thread created, ID = 139785234567891
 * THREAD: I am running! Thread ID = 139785234567891
 * THREAD: Doing some work...
 * THREAD: Work done! Exiting.
 * MAIN  : Thread joined (finished)!
 *
 * ===== DEMO 2: Pass Argument to Thread =====
 * THREAD 1: Hello from thread number 1!
 * THREAD 1: My ID = 139785234567892
 * THREAD 2: Hello from thread number 2!
 * THREAD 2: My ID = 139785234567893
 * THREAD 3: Hello from thread number 3!
 * THREAD 3: My ID = 139785234567894
 * THREAD 1: Done!
 * THREAD 2: Done!
 * THREAD 3: Done!
 * MAIN  : All 3 threads finished!
 *
 * ===== DEMO 3: Return Value from Thread =====
 * THREAD: Calculating 7 x 7...
 * THREAD: Result = 49, returning to main!
 * MAIN  : Thread returned result = 49
 *
 * ===== DEMO 4: Multiple Threads =====
 * MAIN  : Created worker 1
 * MAIN  : Created worker 2
 * MAIN  : Created worker 3
 * MAIN  : Created worker 4
 * WORKER 1: Started
 * WORKER 2: Started
 * WORKER 3: Started
 * WORKER 4: Started
 * WORKER 1: Finished (slept 1 sec)
 * MAIN  : Worker 1 joined!
 * WORKER 2: Finished (slept 2 sec)
 * MAIN  : Worker 2 joined!
 * WORKER 3: Finished (slept 3 sec)
 * MAIN  : Worker 3 joined!
 * WORKER 4: Finished (slept 4 sec)
 * MAIN  : Worker 4 joined!
 * MAIN  : All workers done!
 *
 * ===== DEMO 5: pthread_exit() =====
 * THREAD: Running...
 * THREAD: Calling pthread_exit() now
 * MAIN  : Thread exited cleanly!
 *
 * ===== ALL DEMOS COMPLETE =====
 *
 * ============================================================
 * NOTE: Thread IDs will be DIFFERENT on your machine
 *       Demo 2 print order may vary — OS scheduler decides
 *       Demo 4 finish order is fixed because of sleep()
 * ============================================================
 *
 * QUICK REFERENCE:
 * ──────────────────────────────────────────────────────────
 *  pthread_create(&t, NULL, func, arg) → create thread
 *  pthread_join(t, &retval)            → wait + get return
 *  pthread_self()                      → my thread ID
 *  pthread_exit(val)                   → exit this thread
 *  -lpthread                           → link flag needed
 * ──────────────────────────────────────────────────────────
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>     // all pthread functions
#include <unistd.h>      // sleep()


/* ============================================================
 * DEMO 1: Basic thread creation
 * ============================================================ */
void* basic_thread(void* arg) {
    printf("THREAD: I am running! Thread ID = %lu\n",
           (unsigned long)pthread_self());
    printf("THREAD: Doing some work...\n");
    sleep(1);
    printf("THREAD: Work done! Exiting.\n");
    return NULL;
}

void demo_basic_thread() {
    printf("\n===== DEMO 1: Basic Thread =====\n");

    pthread_t t1;

    pthread_create(&t1, NULL, basic_thread, NULL);

    printf("MAIN  : Thread created, ID = %lu\n",
           (unsigned long)t1);

    pthread_join(t1, NULL);

    printf("MAIN  : Thread joined (finished)!\n");
}


/* ============================================================
 * DEMO 2: Pass argument to thread
 * ============================================================ */
void* thread_with_arg(void* arg) {
    int thread_num = *((int*)arg);

    printf("THREAD %d: Hello from thread number %d!\n",
           thread_num, thread_num);
    printf("THREAD %d: My ID = %lu\n",
           thread_num, (unsigned long)pthread_self());
    sleep(1);
    printf("THREAD %d: Done!\n", thread_num);
    return NULL;
}

void demo_pass_argument() {
    printf("\n===== DEMO 2: Pass Argument to Thread =====\n");

    pthread_t t1, t2, t3;
    int n1 = 1, n2 = 2, n3 = 3;

    pthread_create(&t1, NULL, thread_with_arg, &n1);
    pthread_create(&t2, NULL, thread_with_arg, &n2);
    pthread_create(&t3, NULL, thread_with_arg, &n3);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("MAIN  : All 3 threads finished!\n");
}


/* ============================================================
 * DEMO 3: Return value from thread
 * ============================================================ */
void* thread_return_value(void* arg) {
    int num = *((int*)arg);

    printf("THREAD: Calculating %d x %d...\n", num, num);
    sleep(1);

    /*
     * IMPORTANT: use malloc() NOT local variable
     * Local variable lives on STACK — destroyed when thread exits
     * malloc() lives on HEAP  — survives after thread exits
     */
    int* result = malloc(sizeof(int));
    *result = num * num;

    printf("THREAD: Result = %d, returning to main!\n", *result);
    return (void*)result;
}

void demo_return_value() {
    printf("\n===== DEMO 3: Return Value from Thread =====\n");

    pthread_t t1;
    int num = 7;

    pthread_create(&t1, NULL, thread_return_value, &num);

    void* retval;
    pthread_join(t1, &retval);   // captures thread's return

    int* result = (int*)retval;
    printf("MAIN  : Thread returned result = %d\n", *result);

    free(result);   // always free heap memory!
}


/* ============================================================
 * DEMO 4: Multiple threads using array + loop
 * ============================================================ */
void* worker(void* arg) {
    int id = *((int*)arg);
    printf("WORKER %d: Started\n", id);
    sleep(id);   // worker 1 sleeps 1s, worker 4 sleeps 4s
    printf("WORKER %d: Finished (slept %d sec)\n", id, id);
    return NULL;
}

void demo_multiple_threads() {
    printf("\n===== DEMO 4: Multiple Threads =====\n");

    pthread_t threads[4];
    int ids[4] = {1, 2, 3, 4};

    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, worker, &ids[i]);
        printf("MAIN  : Created worker %d\n", ids[i]);
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
        printf("MAIN  : Worker %d joined!\n", ids[i]);
    }

    printf("MAIN  : All workers done!\n");
}


/* ============================================================
 * DEMO 5: pthread_exit() vs return NULL
 * ============================================================ */
void* thread_exit_demo(void* arg) {
    printf("THREAD: Running...\n");
    printf("THREAD: Calling pthread_exit() now\n");

    /*
     * pthread_exit() → exits ONLY this thread
     * return NULL    → same effect inside thread function
     *
     * KEY DIFFERENCE — when called from main():
     * pthread_exit() → process stays alive until all threads done
     * return 0       → kills ALL threads immediately!
     */
    pthread_exit(NULL);

    printf("THREAD: You will NEVER see this line!\n");
    return NULL;
}

void demo_pthread_exit() {
    printf("\n===== DEMO 5: pthread_exit() =====\n");

    pthread_t t1;
    pthread_create(&t1, NULL, thread_exit_demo, NULL);
    pthread_join(t1, NULL);

    printf("MAIN  : Thread exited cleanly!\n");
}


/* ============================================================
 * MAIN
 * ============================================================ */
int main() {
    printf("========================================\n");
    printf("  lo_threads.c — Thread Management\n");
    printf("========================================\n");
    printf("MAIN  : Main thread ID = %lu\n",
           (unsigned long)pthread_self());

    demo_basic_thread();
    demo_pass_argument();
    demo_return_value();
    demo_multiple_threads();
    demo_pthread_exit();

    printf("\n===== ALL DEMOS COMPLETE =====\n");
    return 0;
}