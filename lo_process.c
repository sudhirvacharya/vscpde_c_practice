#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>      // fork(), getpid(), getppid(), exec()
#include <sys/wait.h>    // wait(), waitpid()
#include <sys/types.h>   // pid_t
/*
CMD FOR EXECUTING
gcc -o lo_process lo_process.c
./lo_process

/*
========================================
  lo_process.c — Process Management
========================================
Main process PID: 5001

===== DEMO 1: Basic fork() =====
PARENT: I am parent! My PID = 5001
PARENT: I created child with PID = 5002
CHILD : I am child!  My PID = 5002
CHILD : My parent's PID = 5001
PARENT: Child finished!

===== DEMO 2: Multiple Children =====
CHILD 1 (PID 5003): Working...
CHILD 2 (PID 5004): Working...
CHILD 1 (PID 5003): Done!
PARENT: Waiting for Child 1 (PID 5003)...
PARENT: Child 1 finished!
PARENT: Waiting for Child 2 (PID 5004)...
CHILD 2 (PID 5004): Done!
PARENT: Child 2 finished!
PARENT: All children done!

===== DEMO 3: Exit Status =====
CHILD : Exiting with status 42
PARENT: Child exited with code = 42

===== DEMO 4: execvp() =====
CHILD : About to exec 'ls -l'
total 24
-rwxr-xr-x 1 user user 16832 Apr 20 10:00 lo_process
-rw-r--r-- 1 user user  3200 Apr 20 10:00 lo_process.c
PARENT: exec child finished!

===== ALL DEMOS COMPLETE =====

/*
 * FILE: lo_process.c
 * TOPIC: Linux OS — Process Management
 * COVERS:
 *   1. fork()     — create child process
 *   2. getpid()   — get current process ID
 *   3. getppid()  — get parent process ID
 *   4. wait()     — parent waits for child
 *   5. waitpid()  — wait for specific child
 *   6. exit()     — terminate process
 *   7. execvp()   — replace process with new program
 *
 * COMPILE: gcc -o lo_process lo_process.c
 * RUN:     ./lo_process
 */

/*
 * ─────────────────────────────────────────
 * MENTAL MODEL
 * ─────────────────────────────────────────
 *
 *   fork() = PHOTOCOPIER 🖨️
 *   Parent = original document
 *   Child  = exact copy
 *   Both run independently after copy!
 *
 *   PROCESS TREE:
 *
 *   main (Parent)
 *       │
 *       ├── fork() ──→ Child 1
 *       │                  └── does work → exit(0)
 *       │
 *       ├── fork() ──→ Child 2
 *       │                  └── does work → exit(0)
 *       │
 *       └── wait() for both → prints final result
 *
 * ─────────────────────────────────────────
 */


/* -----------------------------------------------
 * DEMO 1: Basic fork() — parent and child
 * ----------------------------------------------- */
void demo_basic_fork() {
    printf("\n===== DEMO 1: Basic fork() =====\n");

    pid_t pid = fork();   // creates child process here

    if (pid < 0) {
        // fork failed
        perror("fork failed");
        exit(1);
    }

    else if (pid == 0) {
        /*
         * CHILD PROCESS
         * pid == 0 means "I am the child"
         */
        printf("CHILD : I am child!  My PID = %d\n", getpid());
        printf("CHILD : My parent's PID = %d\n", getppid());
        exit(0);   // child done
    }

    else {
        /*
         * PARENT PROCESS
         * pid > 0 means "I am the parent, child PID = pid"
         */
        printf("PARENT: I am parent! My PID = %d\n", getpid());
        printf("PARENT: I created child with PID = %d\n", pid);

        wait(NULL);   // wait for child to finish
        printf("PARENT: Child finished!\n");
    }
}


/* -----------------------------------------------
 * DEMO 2: Multiple children — waitpid()
 * ----------------------------------------------- */
void demo_multiple_children() {
    printf("\n===== DEMO 2: Multiple Children =====\n");

    pid_t child1, child2;

    /* --- Create Child 1 --- */
    child1 = fork();
    if (child1 == 0) {
        printf("CHILD 1 (PID %d): Working...\n", getpid());
        sleep(1);   // simulate some work
        printf("CHILD 1 (PID %d): Done!\n", getpid());
        exit(0);
    }

    /* --- Create Child 2 --- */
    child2 = fork();
    if (child2 == 0) {
        printf("CHILD 2 (PID %d): Working...\n", getpid());
        sleep(2);   // simulate more work
        printf("CHILD 2 (PID %d): Done!\n", getpid());
        exit(0);
    }

    /*
     * PARENT waits for SPECIFIC child using waitpid()
     * More control than wait() which waits for ANY child
     */
    printf("PARENT: Waiting for Child 1 (PID %d)...\n", child1);
    waitpid(child1, NULL, 0);
    printf("PARENT: Child 1 finished!\n");

    printf("PARENT: Waiting for Child 2 (PID %d)...\n", child2);
    waitpid(child2, NULL, 0);
    printf("PARENT: Child 2 finished!\n");

    printf("PARENT: All children done!\n");
}


/* -----------------------------------------------
 * DEMO 3: exit status — child sends code to parent
 * ----------------------------------------------- */
void demo_exit_status() {
    printf("\n===== DEMO 3: Exit Status =====\n");

    pid_t pid = fork();

    if (pid == 0) {
        /* Child exits with code 42 */
        printf("CHILD : Exiting with status 42\n");
        exit(42);
    }

    else {
        int status;

        /*
         * waitpid() with &status captures child's exit code
         * WIFEXITED(status)   → did child exit normally?
         * WEXITSTATUS(status) → what exit code did it use?
         */
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("PARENT: Child exited with code = %d\n",
                   WEXITSTATUS(status));
        }
    }
}


/* -----------------------------------------------
 * DEMO 4: execvp() — replace process image
 * ----------------------------------------------- */
void demo_exec() {
    printf("\n===== DEMO 4: execvp() =====\n");

    pid_t pid = fork();

    if (pid == 0) {
        /*
         * execvp() REPLACES child process with a new program.
         * Here we run the Unix "ls" command from inside C!
         *
         * char *args[] = command + arguments + NULL terminator
         */
        char *args[] = {"ls", "-l", NULL};

        printf("CHILD : About to exec 'ls -l'\n");

        execvp("ls", args);

        /*
         * If execvp() returns — it FAILED.
         * Normally it never returns (process is replaced).
         */
        perror("execvp failed");
        exit(1);
    }

    else {
        wait(NULL);
        printf("PARENT: exec child finished!\n");
    }
}


/* -----------------------------------------------
 * MAIN — runs all demos
 * ----------------------------------------------- */
int main() {
    printf("========================================\n");
    printf("  lo_process.c — Process Management\n");
    printf("========================================\n");
    printf("Main process PID: %d\n", getpid());

    demo_basic_fork();
    demo_multiple_children();
    demo_exit_status();
    demo_exec();

    printf("\n===== ALL DEMOS COMPLETE =====\n");
    return 0;
}

/*
 * EXPECTED OUTPUT:
 * ========================================
 *   lo_process.c — Process Management
 * ========================================
 * Main process PID: 1234
 *
 * ===== DEMO 1: Basic fork() =====
 * PARENT: I am parent! My PID = 1234
 * PARENT: I created child with PID = 1235
 * CHILD : I am child!  My PID = 1235
 * CHILD : My parent's PID = 1234
 * PARENT: Child finished!
 *
 * ===== DEMO 2: Multiple Children =====
 * CHILD 1 (PID 1236): Working...
 * CHILD 2 (PID 1237): Working...
 * CHILD 1 (PID 1236): Done!
 * PARENT: Child 1 finished!
 * CHILD 2 (PID 1237): Done!
 * PARENT: Child 2 finished!
 * PARENT: All children done!
 *
 * ===== DEMO 3: Exit Status =====
 * CHILD : Exiting with status 42
 * PARENT: Child exited with code = 42
 *
 * ===== DEMO 4: execvp() =====
 * CHILD : About to exec 'ls -l'
 * [output of ls -l command]
 * PARENT: exec child finished!
 *
 * ===== ALL DEMOS COMPLETE =====
 *
 * ─────────────────────────────────────────
 * QUICK REFERENCE:
 * ─────────────────────────────────────────
 * fork()            → create child process
 * getpid()          → my PID
 * getppid()         → my parent's PID
 * wait(NULL)        → wait for ANY child
 * waitpid(pid,...)  → wait for SPECIFIC child
 * exit(code)        → terminate with code
 * execvp(cmd, args) → replace with new program
 * ─────────────────────────────────────────
 */