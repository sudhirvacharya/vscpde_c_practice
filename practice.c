#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

/* ── globals ── */
FILE *f;
pthread_mutex_t file_mutex;

/* ── trace helpers ── */
void trace_begin(const char *name, int tid) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    long us = ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
    pthread_mutex_lock(&file_mutex);
    fprintf(f, "{\"name\":\"%s\",\"ph\":\"B\",\"ts\":%ld,\"pid\":1,\"tid\":%d},\n",
            name, us, tid);
    pthread_mutex_unlock(&file_mutex);
}

void trace_end(const char *name, int tid) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    long us = ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
    pthread_mutex_lock(&file_mutex);
    fprintf(f, "{\"name\":\"%s\",\"ph\":\"E\",\"ts\":%ld,\"pid\":1,\"tid\":%d},\n",
            name, us, tid);
    pthread_mutex_unlock(&file_mutex);
}

/* ════════════════════════════════════
   PASTE YOUR EXPERIMENT HERE
   e.g. semaphore / deadlock / spinlock
   ════════════════════════════════════ */

sem_t data_ready;

void *Producer(void *arg) {
    for (int i = 0; i < 10; i++) {
        trace_begin("producing", 1);
        usleep(3000);
        trace_end("producing", 1);

        trace_begin("sem_post", 1);
        sem_post(&data_ready);
        trace_end("sem_post", 1);

        usleep(2000);
    }
    return NULL;
}

void *Consumer(void *arg) {
    for (int i = 0; i < 10; i++) {
        trace_begin("sem_wait", 2);
        sem_wait(&data_ready);
        trace_end("sem_wait", 2);

        trace_begin("consuming", 2);
        usleep(1000);
        trace_end("consuming", 2);
    }
    return NULL;
}

/* ── main ── */
int main() {
    /* init */
    pthread_mutex_init(&file_mutex, NULL);
    sem_init(&data_ready, 0, 0);

    /* open trace */
    f = fopen("trace.json", "w");
    fprintf(f, "[\n");

    /* run threads */
    pthread_t t1, t2;
    pthread_create(&t1, NULL, Producer, NULL);
    pthread_create(&t2, NULL, Consumer, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    /* close trace */
    fprintf(f, "{}]\n");
    fclose(f);

    /* cleanup */
    pthread_mutex_destroy(&file_mutex);
    sem_destroy(&data_ready);

    printf("trace.json written — open at ui.perfetto.dev\n");
    return 0;
}