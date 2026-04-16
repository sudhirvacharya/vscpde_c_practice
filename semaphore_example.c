#include <stdio.h>       // For printf()
#include <pthread.h>     // For pthread functions (threads)
#include <semaphore.h>   // For semaphore functions ← NEW HEADER
/*
Compile and run:
gcc -o semaphore_example semaphore_example.c -lpthread
./semaphore_example

*/
/*
 * -------------------------------------------------------
 * SEMAPHORE vs MUTEX — What's the difference?
 * -------------------------------------------------------
 *
 * MUTEX  = Toilet with 1 key 🚽
 *          Only 1 person can enter at a time.
 *          The SAME person who locked must unlock.
 *
 * SEMAPHORE = Parking Lot with N slots 🅿️
 *          Multiple people can enter (up to N slots).
 *          ANY person can signal (release a slot).
 *          When slots = 0, everyone WAITS.
 *
 * In this example we use sem value = 1 (binary semaphore)
 * which behaves similar to a mutex.
 * -------------------------------------------------------
 */
sem_t semaphore;   // Declare a semaphore variable

/*
 * Shared variable — both threads will increment this.
 * Without semaphore, threads corrupt each other (race condition).
 */
int shared_counter = 0;


/*
 * -------------------------------------------------------
 * THREAD FUNCTION: increment()
 * -------------------------------------------------------
 * Both Thread 1 and Thread 2 run this same function.
 * Uses semaphore to protect the shared_counter.
 * -------------------------------------------------------
 */
void* increment(void* arg) {

    /* Loop 100,000 times and increment the shared counter */
    for (int i = 0; i < 100000; i++) {

        /*
         * sem_wait() = "Take a slot from parking lot"
         *
         * → If semaphore value > 0 : decrease by 1, enter
         * → If semaphore value = 0 : WAIT (block) until free
         *
         * This is equivalent to pthread_mutex_lock()
         */
        sem_wait(&semaphore);

        /*
         * CRITICAL SECTION
         * Only ONE thread executes this at a time
         * (because we initialized semaphore to 1)
         */
        shared_counter++;

        /*
         * sem_post() = "Give back a slot to parking lot"
         *
         * → Increases semaphore value by 1
         * → Wakes up any thread that was waiting
         *
         * This is equivalent to pthread_mutex_unlock()
         */
        sem_post(&semaphore);

    } // end of for loop

    return NULL; // Thread finished, return nothing
}


/*
 * -------------------------------------------------------
 * MAIN FUNCTION
 * -------------------------------------------------------
 * Program starts here.
 * We initialize semaphore, create 2 threads, wait for them.
 * -------------------------------------------------------
 */
int main() {

    /*
     * pthread_t = Thread ID / Handle
     * t1 and t2 represent our two threads (two workers).
     */
    pthread_t t1, t2;

    /*
     * INITIALIZE the semaphore before using it.
     *
     * sem_init() Arguments:
     *   &semaphore  = semaphore to initialize
     *   0           = 0 means shared between THREADS
     *                 (1 would mean shared between PROCESSES)
     *   1           = INITIAL VALUE of the semaphore
     *                 (1 = only 1 thread allowed at a time)
     *
     * If you set initial value to 3 → 3 threads can enter at once
     */
    sem_init(&semaphore, 0, 1);

    /*
     * CREATE Thread 1
     * → Starts running increment() immediately
     */
    pthread_create(&t1, NULL, increment, NULL);

    /*
     * CREATE Thread 2
     * → Also runs increment() at the same time as Thread 1
     * Both threads now run SIMULTANEOUSLY (parallel)
     */
    pthread_create(&t2, NULL, increment, NULL);

    /*
     * WAIT for Thread 1 to finish.
     * Without this, main() might exit before threads complete!
     */
    pthread_join(t1, NULL);

    /*
     * WAIT for Thread 2 to finish.
     */
    pthread_join(t2, NULL);

    /*
     * DESTROY the semaphore after we are done.
     * Always clean up what you initialize!
     */
    sem_destroy(&semaphore);

    /*
     * Print the final result.
     * Both threads did 100,000 increments each.
     * Expected = 100,000 + 100,000 = 200,000
     * Semaphore ensures the answer is always correct!
     */
    printf("Final counter: %d\n", shared_counter);

    return 0; // Program ended successfully
}

/*

Simple mental model:
Semaphore = Parking Lot 🅿️

Initial value = 1 means only 1 car allowed

Thread 1 arrives → slot available (1→0) → ENTERS
Thread 2 arrives → no slots (0)        → WAITS
Thread 1 leaves  → slot released (0→1) → Thread 2 ENTERS

Semaphore value explained:
sem_init value = 1   → Only 1 thread at a time (like mutex)
sem_init value = 3   → 3 threads allowed simultaneously
sem_init value = 0   → All threads WAIT until someone calls sem_post()

Mutex vs Semaphore — Quick comparison:
Feature            MUTEX 🚽          SEMAPHORE 🅿️
─────────────────────────────────────────────────────
Who can unlock?    Only the locker   Anyone
Count              1 (binary only)   0 to N (any number)
Use case           Protect 1 resource  Control N resources
Header             <pthread.h>       <semaphore.h>
Lock function      pthread_mutex_lock   sem_wait
Unlock function    pthread_mutex_unlock sem_post

*/