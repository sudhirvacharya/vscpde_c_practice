#include <stdio.h>
#include <pthread.h>

int counter = 0;
pthread_mutex_t lock;

void* increment(void* arg) {
    for (int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&lock);   // lock
        counter++;
        pthread_mutex_unlock(&lock); // unlock
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Initialize mutex
    pthread_mutex_init(&lock, NULL);

    // Create threads
    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    // Wait for threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final counter value: %d\n", counter);

    // Destroy mutex
    pthread_mutex_destroy(&lock);

    return 0;
}