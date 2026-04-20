/*
 * ============================================================
 * FILE    : lo_sharedmem.c
 * TOPIC   : Linux OS — Shared Memory between Processes
 * ============================================================
 *
 * COMPILE:
 *   gcc -o lo_sharedmem lo_sharedmem.c -lpthread
 *
 * RUN:
 *   ./lo_sharedmem
 *
 * ============================================================
 * EXPECTED OUTPUT:
 * ============================================================
 *
 *   ========================================
 *     lo_sharedmem.c — Shared Memory
 *   ========================================
 *   MAIN  : Main process PID = 5001
 *
 *   ===== DEMO 1: Basic Shared Memory =====
 *   PARENT: My PID = 5001
 *   CHILD : My PID = 5002
 *   PARENT: Written 100 to shared memory
 *   CHILD : Read value from shared memory = 100
 *   CHILD : Added 50, new value = 150
 *   PARENT: Final value in shared memory = 150
 *
 *   ===== DEMO 2: Shared Counter (Race Condition Safe) =====
 *   PARENT: Starting 100000 increments...
 *   CHILD : Starting 100000 increments...
 *   PARENT: Done incrementing!
 *   CHILD : Done incrementing!
 *   MAIN  : Final counter = 200000 (expected 200000) ✓
 *
 *   ===== DEMO 3: Shared Struct =====
 *   PARENT: Written to shared struct:
 *           name    = HelloFromParent
 *           value   = 42
 *           flag    = 1
 *   CHILD : Read from shared struct:
 *           name    = HelloFromParent
 *           value   = 42
 *           flag    = 1
 *
 *   ===== ALL DEMOS COMPLETE =====
 *   MAIN  : Shared memory released
 *
 * ============================================================
 * NOTE:
 *   PID numbers         → different on your machine
 *   PARENT/CHILD order  → may vary, OS scheduler decides
 *   Final counter       → ALWAYS 200000, semaphore protects it
 * ============================================================
 *
 * WHAT EACH FUNCTION DOES:
 * ──────────────────────────────────────────────────────────
 *  mmap()        → create shared memory region in RAM
 *  munmap()      → release shared memory when done
 *  fork()        → create child process that shares memory
 *  sem_init()    → initialize semaphore inside shared memory
 *  sem_wait()    → LOCK   (like pthread_mutex_lock)
 *  sem_post()    → UNLOCK (like pthread_mutex_unlock)
 *  sem_destroy() → cleanup semaphore
 *  wait()        → parent waits for child to finish
 * ──────────────────────────────────────────────────────────
 *
 * MENTAL MODEL:
 * ──────────────────────────────────────────────────────────
 *  mmap()   = rent a WHITEBOARD both processes can see
 *  sem      = a TOKEN — only holder can write on whiteboard
 *  fork()   = make a copy of current process
 *  munmap() = return the whiteboard when done
 * ──────────────────────────────────────────────────────────
 *
 * COMPARISON:
 * ──────────────────────────────────────────────────────────
 *  lo_mutex.c          │ lo_sharedmem.c
 * ──────────────────────────────────────────────────────────
 *  threads             │ processes (fork)
 *  pthread_mutex       │ semaphore (sem_t)
 *  global variable     │ mmap() shared memory
 *  mutex_lock()        │ sem_wait()
 *  mutex_unlock()      │ sem_post()
 *  pthread_join()      │ wait()
 *  automatic sharing   │ explicit mmap needed
 * ──────────────────────────────────────────────────────────
 *
 * COMMON MISTAKES:
 * ──────────────────────────────────────────────────────────
 *  WRONG: sem_init(&sem, 0, 1) ← pshared=0, threads only
 *  RIGHT: sem_init(&sem, 1, 1) ← pshared=1, across processes
 *
 *  WRONG: MAP_PRIVATE          ← changes NOT visible to child
 *  RIGHT: MAP_SHARED           ← changes visible to all
 *
 *  WRONG: sem_t outside mmap() ← copied by fork, NOT shared
 *  RIGHT: sem_t inside mmap()  ← truly shared by both
 * ──────────────────────────────────────────────────────────
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>          /* fork(), getpid(), sleep()  */
#include <sys/mman.h>        /* mmap(), munmap()           */
#include <sys/wait.h>        /* wait()                     */
#include <semaphore.h>       /* sem_t, sem_init/wait/post  */


/* ============================================================
 * SHARED DATA STRUCTURES
 * ============================================================ */

/* Demo 1 + 2 */
typedef struct {
    int   counter;     /* shared counter                   */
    int   value;       /* simple shared value              */
    sem_t sem;         /* semaphore INSIDE shared memory   */
} SharedBasic;

/* Demo 3 */
typedef struct {
    char  name[32];    /* shared string                    */
    int   value;       /* shared integer                   */
    int   flag;        /* shared flag 0 or 1               */
    sem_t sem;         /* semaphore INSIDE shared memory   */
} SharedStruct;


/* ============================================================
 * DEMO 1: Basic shared memory — parent writes, child reads
 * ============================================================ */
void demo_basic_shared_memory() {
    printf("\n===== DEMO 1: Basic Shared Memory =====\n");

    /*
     * mmap() — create shared memory
     * MAP_SHARED    → changes visible to ALL processes
     * MAP_ANONYMOUS → no file, just RAM
     */
    SharedBasic* shared = mmap(
        NULL,
        sizeof(SharedBasic),
        PROT_READ | PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS,
        -1, 0
    );

    if (shared == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    shared->value = 0;
    sem_init(&shared->sem, 1, 1);  /* pshared=1, value=1 */

    pid_t pid = fork();

    if (pid == 0) {
        /* ── CHILD ── */
        printf("CHILD : My PID = %d\n", getpid());
        sleep(1);   /* wait for parent to write first */

        sem_wait(&shared->sem);                          /* LOCK   */
        printf("CHILD : Read value from shared memory = %d\n",
               shared->value);
        shared->value += 50;
        printf("CHILD : Added 50, new value = %d\n", shared->value);
        sem_post(&shared->sem);                          /* UNLOCK */

        exit(0);
    }
    else {
        /* ── PARENT ── */
        printf("PARENT: My PID = %d\n", getpid());

        sem_wait(&shared->sem);                          /* LOCK   */
        shared->value = 100;
        printf("PARENT: Written 100 to shared memory\n");
        sem_post(&shared->sem);                          /* UNLOCK */

        wait(NULL);   /* wait for child */

        printf("PARENT: Final value in shared memory = %d\n",
               shared->value);
    }

    sem_destroy(&shared->sem);
    munmap(shared, sizeof(SharedBasic));
}


/* ============================================================
 * DEMO 2: Shared counter — both processes increment safely
 * ============================================================ */
void demo_shared_counter() {
    printf("\n===== DEMO 2: Shared Counter (Race Condition Safe) =====\n");

    SharedBasic* shared = mmap(
        NULL,
        sizeof(SharedBasic),
        PROT_READ | PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS,
        -1, 0
    );

    if (shared == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    shared->counter = 0;
    sem_init(&shared->sem, 1, 1);

    pid_t pid = fork();

    if (pid == 0) {
        /* ── CHILD: increment 100000 times ── */
        printf("CHILD : Starting 100000 increments...\n");

        for (int i = 0; i < 100000; i++) {
            sem_wait(&shared->sem);   /* LOCK   */
            shared->counter++;         /* safe!  */
            sem_post(&shared->sem);   /* UNLOCK */
        }

        printf("CHILD : Done incrementing!\n");
        exit(0);
    }
    else {
        /* ── PARENT: increment 100000 times ── */
        printf("PARENT: Starting 100000 increments...\n");

        for (int i = 0; i < 100000; i++) {
            sem_wait(&shared->sem);   /* LOCK   */
            shared->counter++;         /* safe!  */
            sem_post(&shared->sem);   /* UNLOCK */
        }

        printf("PARENT: Done incrementing!\n");

        wait(NULL);   /* wait for child */

        printf("MAIN  : Final counter = %d (expected 200000) %s\n",
               shared->counter,
               shared->counter == 200000 ? "✓" : "✗ ERROR!");
    }

    sem_destroy(&shared->sem);
    munmap(shared, sizeof(SharedBasic));
}


/* ============================================================
 * DEMO 3: Shared struct — pass complex data between processes
 * ============================================================ */
void demo_shared_struct() {
    printf("\n===== DEMO 3: Shared Struct =====\n");

    SharedStruct* shared = mmap(
        NULL,
        sizeof(SharedStruct),
        PROT_READ | PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS,
        -1, 0
    );

    if (shared == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    memset(shared->name, 0, sizeof(shared->name));
    shared->value = 0;
    shared->flag  = 0;
    sem_init(&shared->sem, 1, 1);

    pid_t pid = fork();

    if (pid == 0) {
        /* ── CHILD: read the struct ── */
        sleep(1);   /* wait for parent to write */

        sem_wait(&shared->sem);
        printf("CHILD : Read from shared struct:\n");
        printf("        name    = %s\n", shared->name);
        printf("        value   = %d\n", shared->value);
        printf("        flag    = %d\n", shared->flag);
        sem_post(&shared->sem);

        exit(0);
    }
    else {
        /* ── PARENT: write to the struct ── */
        sem_wait(&shared->sem);
        strncpy(shared->name, "HelloFromParent",
                sizeof(shared->name) - 1);
        shared->value = 42;
        shared->flag  = 1;
        printf("PARENT: Written to shared struct:\n");
        printf("        name    = %s\n", shared->name);
        printf("        value   = %d\n", shared->value);
        printf("        flag    = %d\n", shared->flag);
        sem_post(&shared->sem);

        wait(NULL);
    }

    sem_destroy(&shared->sem);
    munmap(shared, sizeof(SharedStruct));
}


/* ============================================================
 * MAIN
 * ============================================================ */
int main() {
    printf("========================================\n");
    printf("  lo_sharedmem.c — Shared Memory\n");
    printf("========================================\n");
    printf("MAIN  : Main process PID = %d\n", getpid());

    demo_basic_shared_memory();
    demo_shared_counter();
    demo_shared_struct();

    printf("\n===== ALL DEMOS COMPLETE =====\n");
    printf("MAIN  : Shared memory released\n");

    return 0;
}