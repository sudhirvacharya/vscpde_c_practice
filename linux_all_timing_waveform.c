#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>
#include <stdlib.h>

/* ══════════════════════════════════════════
   SELECT EXPERIMENT — set one to 1, rest 0
   ══════════════════════════════════════════ */
#define EXP_ROUND_ROBIN        0
#define EXP_PRIORITY_INVERSION 0
#define EXP_DEADLOCK           0
#define EXP_SEMAPHORE_PC       0
#define EXP_COUNTING_SEM       0
#define EXP_SPINLOCK_VS_MUTEX  0
#define EXP_THREAD_POOL        0
#define EXP_SCHEDULER          1   /* ← currently active */

/* ══════════════════════════════════════════
   SCHEDULER TASK PERIODS (microseconds)
   Modify these to change timing
   ══════════════════════════════════════════ */
#define TASK_1MS_PERIOD    1000
#define TASK_2MS_PERIOD    2000
#define TASK_5MS_PERIOD    5000
#define TASK_10MS_PERIOD  10000

#define TASK_1MS_EXEC      400    /* execution time 0.4ms  */
#define TASK_2MS_EXEC      800    /* execution time 0.8ms  */
#define TASK_5MS_EXEC     2000    /* execution time 2ms    */
#define TASK_10MS_EXEC    4000    /* execution time 4ms    */

#define SCHED_RUNTIME_MS   10   /* total run = 100ms     */
#define SCHED_ITERATIONS    5   /* max loop iterations   */

/* ── globals ── */
FILE            *f;
pthread_mutex_t  file_mutex;

/* ── add this global flag (near other globals) ── */
volatile int spi_wants_cpu = 0;  /* SPI sets this before running */
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
    usleep(3000);
    trace_begin("MED_running_free", 2);
    printf("[MED]  running freely — delays LOW further\n");
    usleep(5000);
    trace_end("MED_running_free", 2);
    return NULL;
}

void *HighPriorityTask(void *arg) {
    usleep(2000);
    printf("[HIGH] wants mutex — blocking now\n");
    trace_begin("HIGH_blocked_on_mutex", 3);
    pthread_mutex_lock(&shared_mutex);
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
    pthread_mutex_lock(&mutex2);
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
    pthread_mutex_lock(&mutex1);
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
    pthread_join(t1, NULL);
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
        sem_wait(&data_ready);
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
        sem_wait(&slots_free);
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
        sem_wait(&slots_used);
        trace_end("wait_used_slot", 2);

        trace_begin("read_buffer", 2);
        printf("[C] reading item %d\n", i);
        usleep(3000);
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
   Perfetto: spinlock=no gap, mutex=gap
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
    pthread_spin_lock(&spinlock);
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
    pthread_mutex_lock(&slp_mutex);
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
        printf("[W%d] running job %d (%dms)\n", id, job, job);
        usleep(job * 1000);
        trace_end(name, id);
    }
    return NULL;
}

void run_experiment(void) {
    pthread_mutex_init(&queue_mutex, NULL);
    for (int i = 0; i < JOBS; i++)
        job_queue[i] = (i % 5 + 1) * 2;

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
   EXP 8 — MULTI-PERIOD SCHEDULER
   Simulates 4 periodic RTOS tasks:

   Task      Period   Exec    Maps to
   ────────  ───────  ──────  ─────────────────
   1ms_task   1ms     0.4ms   ADC read / sensor
   2ms_task   2ms     0.8ms   SPI comm / filter
   5ms_task   5ms     2.0ms   CAN tx / control
   10ms_task  10ms    4.0ms   UART log / diag

   Each task fires at its period using
   absolute deadline tracking — same as
   vTaskDelayUntil() in FreeRTOS

   Perfetto: 4 rows, see preemption,
   deadline miss if exec > period
   ══════════════════════════════════════════ */
/* ══════════════════════════════════════════
   EXP 8 — MULTI-PERIOD SCHEDULER
   UART (10ms) sliced — yields every 2ms to SPI
   ══════════════════════════════════════════ */
#if EXP_SCHEDULER

/* UART slice size = SPI period so SPI always preempts cleanly */
#define UART_SLICE_US   TASK_2MS_PERIOD   /* 2000us per UART slice */

pthread_mutex_t spi_mutex;   /* UART holds this while in a slice  */
pthread_cond_t  spi_done;    /* SPI signals UART after each run   */
volatile int    spi_running; /* flag: 1=SPI wants CPU, 0=idle     */

void adc_read_task(void)    { printf("[1ms ] ADC read\n"); }
void spi_filter_task(void)  { printf("[2ms ] SPI comm + filter\n"); }
void can_control_task(void) { printf("[5ms ] CAN tx + control loop\n"); }
void uart_diag_task(void)   { printf("[10ms] UART log + diagnostics\n"); }

static long now_us(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000000L + ts.tv_nsec / 1000;
}

/* ── ADC: unchanged periodic task ── */
void *task_adc(void *arg) {
    long next = now_us();
    int  max  = 10;
    for (int i = 0; i < max; i++) {
        long n = now_us();
        if (next > n) usleep((useconds_t)(next - n));

        if (now_us() > next + 100) {
            trace_begin("1ms_ADC_DEADLINE_MISS", 1);
            trace_end  ("1ms_ADC_DEADLINE_MISS", 1);
        }
        trace_begin("1ms_ADC", 1);
        adc_read_task();
        usleep(TASK_1MS_EXEC);
        trace_end("1ms_ADC", 1);

        next += TASK_1MS_PERIOD;
    }
    return NULL;
}

void *task_spi(void *arg) {
    long next = now_us();
    int  max  = 5;

    for (int i = 0; i < max; i++) {
        long n = now_us();
        if (next > n) usleep((useconds_t)(next - n));

        if (now_us() > next + 100) {
            trace_begin("2ms_SPI_DEADLINE_MISS", 2);
            trace_end  ("2ms_SPI_DEADLINE_MISS", 2);
        }

        /* signal UART to pause */
        spi_wants_cpu = 1;
        usleep(50);   /* small gap — let UART notice the flag */

        trace_begin("2ms_SPI", 2);
        spi_filter_task();
        usleep(TASK_2MS_EXEC);
        trace_end("2ms_SPI", 2);

        /* signal UART to resume */
        spi_wants_cpu = 0;

        next += TASK_2MS_PERIOD;
    }
    return NULL;
}

void *task_uart(void *arg) {
    long next = now_us();
    int  max  = 1;

    for (int i = 0; i < max; i++) {
        long n = now_us();
        if (next > n) usleep((useconds_t)(next - n));

        if (now_us() > next + 100) {
            trace_begin("10ms_UART_DEADLINE_MISS", 4);
            trace_end  ("10ms_UART_DEADLINE_MISS", 4);
        }

        uart_diag_task();

        int remaining_us = TASK_10MS_EXEC;  /* 4000us total */

        while (remaining_us > 0) {

            /* ── pause if SPI wants CPU ── */
            if (spi_wants_cpu) {
                trace_begin("10ms_UART_WAITING", 4);
                while (spi_wants_cpu)
                    usleep(100);   /* spin-wait until SPI clears flag */
                trace_end("10ms_UART_WAITING", 4);
            }

            /* ── run one 2ms slice ── */
            int slice = (remaining_us < UART_SLICE_US)
                        ? remaining_us : UART_SLICE_US;

            trace_begin("10ms_UART", 4);
            usleep((useconds_t)slice);
            trace_end("10ms_UART", 4);

            remaining_us -= slice;
        }

        next += TASK_10MS_PERIOD;
    }
    return NULL;
}

/* ── CAN: unchanged periodic task ── */
void *task_can(void *arg) {
    long next = now_us();
    int  max  = 2;
    for (int i = 0; i < max; i++) {
        long n = now_us();
        if (next > n) usleep((useconds_t)(next - n));

        if (now_us() > next + 100) {
            trace_begin("5ms_CAN_DEADLINE_MISS", 3);
            trace_end  ("5ms_CAN_DEADLINE_MISS", 3);
        }
        trace_begin("5ms_CAN", 3);
        can_control_task();
        usleep(TASK_5MS_EXEC);
        trace_end("5ms_CAN", 3);

        next += TASK_5MS_PERIOD;
    }
    return NULL;
}



void run_experiment(void) {
    pthread_mutex_init(&spi_mutex, NULL);
    pthread_cond_init (&spi_done,  NULL);
    spi_running = 0;

    pthread_t t1, t2, t3, t4;
printf("=== Sliced Scheduler started ===\n");
printf("UART sliced every %dus, preempted by SPI\n\n", UART_SLICE_US);

    pthread_create(&t1, NULL, task_adc,  NULL);
    pthread_create(&t2, NULL, task_spi,  NULL);
    pthread_create(&t3, NULL, task_can,  NULL);
    pthread_create(&t4, NULL, task_uart, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);

    pthread_mutex_destroy(&spi_mutex);
    pthread_cond_destroy (&spi_done);
    printf("\n=== Scheduler done ===\n");
}

#endif /* EXP_SCHEDULER */




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