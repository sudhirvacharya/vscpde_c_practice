#include <stdio.h>      // For printf()
#include <pthread.h>    // For pthread functions (threads, mutex)


//commnd for running
/*
@sudhirvacharya ➜ /workspaces/vscpde_c_practice (main) $ gcc -o mutex_example mutex_example.c -lpthread
@sudhirvacharya ➜ /workspaces/vscpde_c_practice (main) $ ./mutex_example
Final counter: 200000

*/
/* 
 * Mutex (Mutual Exclusion Lock)
 * Think of it like a TOILET LOCK 🚽
 * Only ONE person (thread) can use it at a time.
 * Others WAIT outside until the lock is released.
 */
pthread_mutex_t lock;

/*
 * This is the SHARED variable — both threads will try to
 * increment this at the same time. Without mutex, they
 * would corrupt each other's work (race condition).
 */
int shared_counter = 0;


/*
 * -------------------------------------------------------
 * THREAD FUNCTION: increment()
 * -------------------------------------------------------
 * This function runs INSIDE a thread.
 * Both Thread 1 and Thread 2 will run this same function.
 *
 * void* arg  → input  (we are not passing anything, so NULL)
 * void*      → output (we are not returning anything, so NULL)
 * -------------------------------------------------------
 */
void* increment(void* arg) {

    /* Loop 100,000 times and increment the shared counter */
    for (int i = 0; i < 100000; i++) {

        /*
         * LOCK the mutex before touching shared_counter.
         * If another thread already has the lock,
         * THIS thread will WAIT here until it's free.
         */
        pthread_mutex_lock(&lock);

        /*
         * CRITICAL SECTION — only ONE thread runs this at a time.
         * Safe to modify shared_counter here.
         */
        shared_counter++;

        /*
         * UNLOCK the mutex so the other thread can now
         * enter the critical section.
         */
        pthread_mutex_unlock(&lock);

    } // end of for loop

    return NULL; // Thread finished, return nothing
}


/*
 * -------------------------------------------------------
 * MAIN FUNCTION
 * -------------------------------------------------------
 * Program starts here.
 * We create 2 threads and wait for them to finish.
 * -------------------------------------------------------
 */
int main() {

    /*
     * pthread_t = Thread ID / Handle
     * t1 and t2 represent our two threads.
     * Think of them like two workers.
     */
    pthread_t t1, t2;

    /*
     * INITIALIZE the mutex before using it.
     * NULL = use default settings.
     * Always do this BEFORE creating threads.
     */
    pthread_mutex_init(&lock, NULL);

    /*
     * CREATE Thread 1
     * → It will start running increment() immediately.
     * Arguments:
     *   &t1        = store thread ID here
     *   NULL       = default thread settings
     *   increment  = function to run in the thread
     *   NULL       = no argument to pass to increment()
     */
    pthread_create(&t1, NULL, increment, NULL);

    /*
     * CREATE Thread 2
     * → It also runs increment() at the same time as Thread 1.
     * Both threads now run SIMULTANEOUSLY (parallel).
     */
    pthread_create(&t2, NULL, increment, NULL);

    /*
     * WAIT for Thread 1 to finish before moving on.
     * Without this, main() might exit before threads are done!
     * NULL = we don't care about thread's return value.
     */
    pthread_join(t1, NULL);

    /*
     * WAIT for Thread 2 to finish.
     */
    pthread_join(t2, NULL);

    /*
     * DESTROY the mutex after we are done using it.
     * Frees up the resources used by the mutex.
     * Always clean up what you initialize!
     */
    pthread_mutex_destroy(&lock);

    /*
     * Print the final result.
     * Since both threads did 100,000 increments each:
     * Expected result = 100,000 + 100,000 = 200,000
     * Thanks to mutex, the answer will always be correct!
     */
    printf("Final counter: %d\n", shared_counter);

    return 0; // Program ended successfully
}

/*

Simple mental model to remember:
Mutex = Toilet Lock 🚽

Thread 1 enters → LOCKS door → does work → UNLOCKS door
Thread 2 arrives → sees LOCKED → WAITS → enters when free
Without Mutex ❌         With Mutex ✅
─────────────────        ─────────────────
Both read  → 5           T1 reads  → 5
Both write → 6           T1 writes → 6
Lost one increment!      T2 reads  → 6
Result: WRONG            T2 writes → 7
                         Result: CORRECT


                         main() starts
│
├── pthread_create(&t1, ..., increment, ...)
│       └── OS creates Thread 1 → starts running increment()
│               └── loops 100000 times, locking/unlocking mutex
│
├── pthread_create(&t2, ..., increment, ...)
│       └── OS creates Thread 2 → starts running increment()
│               └── loops 100000 times, locking/unlocking mutex
│
├── pthread_join(t1) → main BLOCKS here until Thread 1 finishes
├── pthread_join(t2) → main BLOCKS here until Thread 2 finishes
│
└── prints final counter = 200000

*/