
//gcc -o lo_bin_Semaphor lo_bin_Semaphor.c
#include <stdio.h>
#include <pthread.h>      /* for pthread_create, pthread_join, pthread_t */
#include <semaphore.h>    /* for sem_t, sem_init, sem_wait, sem_post, sem_destroy */
#include <unistd.h>        /* for sleep() */

sem_t bin_sem;   /* global semaphore, shared by both threads.
                     It's just a counter with wait/wake logic built in. */

void *producer(void *arg)
{
    sleep(1);
    /* Simulates "doing some work" or waiting for a hardware event
       before the signal actually happens (like an ISR firing after
       some real-world delay). */

    printf("Producer: event occurred, giving semaphore\n");

    sem_post(&bin_sem);
    /* Increments bin_sem from 0 -> 1.
       If another thread is currently blocked in sem_wait() on this
       semaphore, this call wakes it up.
       Equivalent to FreeRTOS's xSemaphoreGiveFromISR() when called
       from an interrupt context. */

    return NULL;
}

void *consumer(void *arg)
{
    printf("Consumer: waiting for semaphore\n");

    sem_wait(&bin_sem);
    /* Tries to decrement bin_sem.
       Since bin_sem starts at 0, there's nothing to take yet, so
       this thread BLOCKS here (goes to sleep) until some other
       thread calls sem_post() and raises the value above 0.
       Equivalent to FreeRTOS's xSemaphoreTake(). */

    printf("Consumer: event handled!\n");
    /* This line only runs after sem_wait() unblocks, meaning the
       producer has definitely already signaled the event. */

    return NULL;
}

int main(void)
{
    sem_init(&bin_sem, 0, 0);
    /* Initialize the semaphore:
       - 2nd arg (0): shared between threads in this process,
         not across separate processes
       - 3rd arg (0): starting value is 0, i.e. "unavailable"/"taken"
         This is what makes it behave like a binary semaphore that
         starts empty - consumer must wait for a give before proceeding. */

    pthread_t t1, t2;

    pthread_create(&t2, NULL, consumer, NULL);
    /* Starts the consumer thread. It will likely reach sem_wait()
       and block almost immediately, since bin_sem is still 0. */

    pthread_create(&t1, NULL, producer, NULL);
    /* Starts the producer thread. It sleeps 1 second, then posts
       to the semaphore, unblocking the consumer. */

    pthread_join(t1, NULL);
    /* Waits for the producer thread to fully finish before continuing. */

    pthread_join(t2, NULL);
    /* Waits for the consumer thread to fully finish before continuing.
       Without these two joins, main() could exit before the threads
       finish, killing the program early. */

    sem_destroy(&bin_sem);
    /* Cleans up the semaphore's resources. Good practice once you're
       done using it, though not strictly required right before exit. */

    return 0;
}