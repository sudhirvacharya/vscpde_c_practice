#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>

//steps
//run this cmd
//gcc -Wall -o linux_all_timing_waveform linux_all_timing_waveform.c -lpthread && ./linux_all_timing_waveform
//it will generate trace.json
//import this and analize  https://ui.perfetto.dev/#!/viewer?local_cache_key=00000000-0000-0000-4907-90da9561b115

/* ══════════════════════════════════════════
   SELECT EXPERIMENT — set one to 1, rest 0
   ══════════════════════════════════════════ */
#define EXP_ROUND_ROBIN       0
#define EXP_PRIORITY_INVERSION 0
#define EXP_DEADLOCK          0
#define EXP_SEMAPHORE_PC      1   /* ← currently active */
#define EXP_COUNTING_SEM      0
#define EXP_SPINLOCK_VS_MUTEX 0
#define EXP_THREAD_POOL       0

/* ── globals ── */
FILE            *f;
pthread_mutex_t  file_mutex;

/* ══════════════════════════════════════════
   TRACE HELPERS — do not modify
   ══════════════════════════════════════════ */
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

/* ══════════════════════════════════════════
   EXP 1 — ROUND ROBIN
   Two equal priority threads take turns
   Perfetto: alternating equal-width blocks
   ══════════════════════════════════════════ */
#if EXP_ROUND_ROBIN

void *EnglishThread(void *arg) {
    for (int i = 0; i < 10; i++) {
        trace_begin("EnglishThread", 1);
        printf("Hello %d\n", i);
        usleep(3000);
        trace_end("EnglishThread", 1);
        usleep(1000);
    }
    return NULL;
}

void *FrenchThread(void *arg) {
    for (int i = 0; i < 10; i++) {
        trace_begin("FrenchThread", 2);
        printf("Bonjour %d\n", i);
        usleep(3000);
        trace_end("FrenchThread", 2);
        usleep(1000);
    }
    return NULL;
}

void run_experiment(void) {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, EnglishThread, NULL);
    pthread_create(&t2, NULL, FrenchThread,  NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}

#endif /* EXP_ROUND_ROBIN */

/* ══════════════════════════════════════════
   EXP 2 — PRIORITY INVERSION
   LOW holds mutex → HIGH starves
   MED runs freely → makes it worse
   Perfetto: HIGH blocked while MED runs free
   ══════════════════════════════════════════ */
#if EXP_PRIORITY_INVERSION

pthread_mutex_t shared_mutex;

void *LowPriorityTask(void *arg) {
    pthread_mutex_lock(&shared_mutex);
    trace_begin("LOW_holds_mutex", 1);
    printf("[LOW]  acquired mutex, doing 10ms work\n");
    usleep(10000);
    trace_end("LOW_holds_mutex", 1);
    pthread_mutex_unlock(&shared_mutex);
    printf("[LOW]  released mutex\n");
    return NULL;
}

void *MedPriorityTask(void *arg) {
    usleep(3000);   /* starts at 3ms */
    trace_begin("MED_running_free", 2);
    printf("[MED]  running freely — delays LOW further\n");
    usleep(5000);
    trace_end("MED_running_free", 2);
    return NULL;
}

void *HighPriorityTask(void *arg) {
    usleep(2000);   /* starts at 2ms */
    printf("[HIGH] wants mutex — blocking now\n");
    trace_begin("HIGH_blocked_on_mutex", 3);
    pthread_mutex_lock(&shared_mutex);   /* blocks here */
    trace_end("HIGH_blocked_on_mutex", 3);
    trace_begin("HIGH_running", 3);
    printf("[HIGH] got mutex — finally running\n");
    usleep(1000);
    trace_end("HIGH_running", 3);
    pthread_mutex_unlock(&shared_mutex);
    return NULL;
}

void run_experiment(void) {
    pthread_mutex_init(&shared_mutex, NULL);
    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, LowPriorityTask,  NULL);
    pthread_create(&t2, NULL, MedPriorityTask,  NULL);
    pthread_create(&t3, NULL, HighPriorityTask, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_mutex_destroy(&shared_mutex);
}

#endif /* EXP_PRIORITY_INVERSION */

/* ══════════════════════════════════════════
   EXP 3 — DEADLOCK
   TaskA holds M1 wants M2
   TaskB holds M2 wants M1
   Both freeze forever
   Perfetto: trace blocks never close
   NOTE: program will hang — Ctrl+C to stop
   ══════════════════════════════════════════ */
#if EXP_DEADLOCK

pthread_mutex_t mutex1, mutex2;

void *TaskA(void *arg) {
    printf("[A] locking mutex1\n");
    pthread_mutex_lock(&mutex1);
    trace_begin("A_holds_M1", 1);
    usleep(2000);
    printf("[A] wants mutex2 — will deadlock\n");
    pthread_mutex_lock(&mutex2);   /* DEADLOCK */
    trace_end("A_holds_M1", 1);
    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);
    return NULL;
}

void *TaskB(void *arg) {
    printf("[B] locking mutex2\n");
    pthread_mutex_lock(&mutex2);
    trace_begin("B_holds_M2", 2);
    usleep(2000);
    printf("[B] wants mutex1 — will deadlock\n");
    pthread_mutex_lock(&mutex1);   /* DEADLOCK */
    trace_end("B_holds_M2", 2);
    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);
    return NULL;
}

void run_experiment(void) {
    pthread_mutex_init(&mutex1, NULL);
    pthread_mutex_init(&mutex2, NULL);
    pthread_t t1, t2;
    pthread_create(&t1, NULL, TaskA, NULL);
    pthread_create(&t2, NULL, TaskB, NULL);
    pthread_join(t1, NULL);   /* hangs here */
    pthread_join(t2, NULL);
    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);
}

#endif /* EXP_DEADLOCK */

/* ══════════════════════════════════════════
   EXP 4 — SEMAPHORE PRODUCER / CONSUMER
   Producer signals every 3ms
   Consumer blocks until signal arrives
   Perfetto: consumer gaps = waiting for sem
   ══════════════════════════════════════════ */
#if EXP_SEMAPHORE_PC

sem_t data_ready;

void *Producer(void *arg) {
    for (int i = 0; i < 10; i++) {
        trace_begin("producing", 1);
        printf("[P] producing item %d\n", i);
        usleep(3000);
        trace_end("producing", 1);

        trace_begin("sem_post", 1);
        sem_post(&data_ready);
        printf("[P] posted semaphore %d\n", i);
        trace_end("sem_post", 1);

        usleep(2000);
    }
    return NULL;
}

void *Consumer(void *arg) {
    for (int i = 0; i < 10; i++) {
        trace_begin("sem_wait_blocking", 2);
        printf("[C] waiting for item %d\n", i);
        sem_wait(&data_ready);          /* blocks until post */
        trace_end("sem_wait_blocking", 2);

        trace_begin("consuming", 2);
        printf("[C] consuming item %d\n", i);
        usleep(1000);
        trace_end("consuming", 2);
    }
    return NULL;
}

void run_experiment(void) {
    sem_init(&data_ready, 0, 0);
    pthread_t t1, t2;
    pthread_create(&t1, NULL, Producer, NULL);
    pthread_create(&t2, NULL, Consumer, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    sem_destroy(&data_ready);
}

#endif /* EXP_SEMAPHORE_PC */

/* ══════════════════════════════════════════
   EXP 5 — COUNTING SEMAPHORE (buffer slots)
   Buffer holds max 3 items
   Producer stalls when buffer full
   Consumer frees slots
   Perfetto: producer pauses at count=3
   ══════════════════════════════════════════ */
#if EXP_COUNTING_SEM

#define BUFFER_SIZE 3
sem_t slots_free;
sem_t slots_used;

void *CountProducer(void *arg) {
    for (int i = 0; i < 12; i++) {
        trace_begin("wait_free_slot", 1);
        sem_wait(&slots_free);          /* stall if buffer full */
        trace_end("wait_free_slot", 1);

        trace_begin("write_buffer", 1);
        printf("[P] writing item %d\n", i);
        usleep(500);
        trace_end("write_buffer", 1);

        sem_post(&slots_used);
    }
    return NULL;
}

void *CountConsumer(void *arg) {
    for (int i = 0; i < 12; i++) {
        trace_begin("wait_used_slot", 2);
        sem_wait(&slots_used);          /* stall if buffer empty */
        trace_end("wait_used_slot", 2);

        trace_begin("read_buffer", 2);
        printf("[C] reading item %d\n", i);
        usleep(3000);                   /* slow consumer */
        trace_end("read_buffer", 2);

        sem_post(&slots_free);
    }
    return NULL;
}

void run_experiment(void) {
    sem_init(&slots_free, 0, BUFFER_SIZE);
    sem_init(&slots_used, 0, 0);
    pthread_t t1, t2;
    pthread_create(&t1, NULL, CountProducer, NULL);
    pthread_create(&t2, NULL, CountConsumer, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    sem_destroy(&slots_free);
    sem_destroy(&slots_used);
}

#endif /* EXP_COUNTING_SEM */

/* ══════════════════════════════════════════
   EXP 6 — SPINLOCK VS MUTEX
   Spinlock burns CPU while waiting
   Mutex sleeps and yields CPU
   Perfetto: spinlock = no gap, mutex = gap
   ══════════════════════════════════════════ */
#if EXP_SPINLOCK_VS_MUTEX

pthread_spinlock_t spinlock;
pthread_mutex_t    slp_mutex;

void *SpinHolder(void *arg) {
    pthread_spin_lock(&spinlock);
    trace_begin("spin_holder_critical", 1);
    printf("[SPIN-H] holding spinlock 8ms\n");
    usleep(8000);
    trace_end("spin_holder_critical", 1);
    pthread_spin_unlock(&spinlock);
    return NULL;
}

void *SpinWaiter(void *arg) {
    usleep(1000);
    trace_begin("spin_waiter_burning_cpu", 2);
    printf("[SPIN-W] spinning — burning CPU\n");
    pthread_spin_lock(&spinlock);   /* busy waits */
    trace_end("spin_waiter_burning_cpu", 2);
    trace_begin("spin_waiter_critical", 2);
    usleep(1000);
    trace_end("spin_waiter_critical", 2);
    pthread_spin_unlock(&spinlock);
    return NULL;
}

void *MutexHolder(void *arg) {
    pthread_mutex_lock(&slp_mutex);
    trace_begin("mutex_holder_critical", 3);
    printf("[MTX-H] holding mutex 8ms\n");
    usleep(8000);
    trace_end("mutex_holder_critical", 3);
    pthread_mutex_unlock(&slp_mutex);
    return NULL;
}

void *MutexWaiter(void *arg) {
    usleep(1000);
    trace_begin("mutex_waiter_sleeping", 4);
    printf("[MTX-W] sleeping — yields CPU\n");
    pthread_mutex_lock(&slp_mutex);  /* sleeps */
    trace_end("mutex_waiter_sleeping", 4);
    trace_begin("mutex_waiter_critical", 4);
    usleep(1000);
    trace_end("mutex_waiter_critical", 4);
    pthread_mutex_unlock(&slp_mutex);
    return NULL;
}

void run_experiment(void) {
    pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);
    pthread_mutex_init(&slp_mutex, NULL);
    pthread_t t1, t2, t3, t4;
    pthread_create(&t1, NULL, SpinHolder,  NULL);
    pthread_create(&t2, NULL, SpinWaiter,  NULL);
    pthread_create(&t3, NULL, MutexHolder, NULL);
    pthread_create(&t4, NULL, MutexWaiter, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_spin_destroy(&spinlock);
    pthread_mutex_destroy(&slp_mutex);
}

#endif /* EXP_SPINLOCK_VS_MUTEX */

/* ══════════════════════════════════════════
   EXP 7 — THREAD POOL
   4 workers, 20 jobs of varying duration
   Perfetto: 4 rows, load spread across all
   ══════════════════════════════════════════ */
#if EXP_THREAD_POOL

#define WORKERS  4
#define JOBS     20

int             job_queue[JOBS];
int             job_head = 0;
pthread_mutex_t queue_mutex;

void *Worker(void *arg) {
    int  id = *(int *)arg;
    char name[32];
    sprintf(name, "worker_%d", id);

    while (1) {
        pthread_mutex_lock(&queue_mutex);
        if (job_head >= JOBS) {
            pthread_mutex_unlock(&queue_mutex);
            break;
        }
        int job = job_queue[job_head++];
        pthread_mutex_unlock(&queue_mutex);

        trace_begin(name, id);
        printf("[W%d] running job %d (%d ms)\n", id, job, job);
        usleep(job * 1000);
        trace_end(name, id);
    }
    return NULL;
}

void run_experiment(void) {
    pthread_mutex_init(&queue_mutex, NULL);

    /* fill job queue with varying durations 1..20ms */
    for (int i = 0; i < JOBS; i++)
        job_queue[i] = (i % 5 + 1) * 2;   /* 2,4,6,8,10ms pattern */

    pthread_t threads[WORKERS];
    int       ids[WORKERS];
    for (int i = 0; i < WORKERS; i++) {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, Worker, &ids[i]);
    }
    for (int i = 0; i < WORKERS; i++)
        pthread_join(threads[i], NULL);

    pthread_mutex_destroy(&queue_mutex);
}

#endif /* EXP_THREAD_POOL */

/* ══════════════════════════════════════════
   MAIN — do not modify
   ══════════════════════════════════════════ */
int main(void) {
    pthread_mutex_init(&file_mutex, NULL);

    f = fopen("trace.json", "w");
    if (!f) { perror("fopen"); return 1; }
    fprintf(f, "[\n");

    run_experiment();

    fprintf(f, "{}]\n");
    fclose(f);
    pthread_mutex_destroy(&file_mutex);

    printf("\ntrace.json written — open at ui.perfetto.dev\n");
    return 0;
}