//gcc -o lo_pipe lo_pipe.c
//./lo_pipe

// lo_pipe.c - Pipes with fork
// Concepts: pipe(), fork(), read(), write(), close()

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

// ─────────────────────────────────────────
// DEMO 1: Basic pipe — child sends to parent
// ─────────────────────────────────────────
void demo_basic_pipe() {
    printf("\n=== DEMO 1: Basic Pipe (child → parent) ===\n");

    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }
    // fd[0] = read end
    // fd[1] = write end

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);

    } else if (pid == 0) {
        // ── CHILD: writer ──
        close(fd[0]);                          // close unused read end

        char *msg = "Hello from child!";
        write(fd[1], msg, strlen(msg) + 1);    // +1 to include '\0'
        printf("[Child]  Sent: \"%s\"\n", msg);

        close(fd[1]);
        exit(0);

    } else {
        // ── PARENT: reader ──
        close(fd[1]);                          // close unused write end

        char buf[64];
        read(fd[0], buf, sizeof(buf));
        printf("[Parent] Received: \"%s\"\n", buf);

        close(fd[0]);
        wait(NULL);
    }
}

// ─────────────────────────────────────────
// DEMO 2: Parent sends to child
// ─────────────────────────────────────────
void demo_parent_to_child() {
    printf("\n=== DEMO 2: Basic Pipe (parent → child) ===\n");

    int fd[2];
    pipe(fd);

    pid_t pid = fork();

    if (pid == 0) {
        // ── CHILD: reader ──
        close(fd[1]);

        char buf[64];
        int n = read(fd[0], buf, sizeof(buf));
        buf[n] = '\0';
        printf("[Child]  Received: \"%s\"\n", buf);

        close(fd[0]);
        exit(0);

    } else {
        // ── PARENT: writer ──
        close(fd[0]);

        char *msg = "Hello from parent!";
        write(fd[1], msg, strlen(msg));
        printf("[Parent] Sent: \"%s\"\n", msg);

        close(fd[1]);
        wait(NULL);
    }
}

// ─────────────────────────────────────────
// DEMO 3: Two-way communication (2 pipes)
// ─────────────────────────────────────────
void demo_two_way() {
    printf("\n=== DEMO 3: Two-Way Pipe ===\n");

    int parent_to_child[2];   // parent writes, child reads
    int child_to_parent[2];   // child writes, parent reads

    pipe(parent_to_child);
    pipe(child_to_parent);

    pid_t pid = fork();

    if (pid == 0) {
        // ── CHILD ──
        close(parent_to_child[1]);   // not writing to this
        close(child_to_parent[0]);   // not reading from this

        // Read question from parent
        char question[64];
        int n = read(parent_to_child[0], question, sizeof(question));
        question[n] = '\0';
        printf("[Child]  Got question: \"%s\"\n", question);

        // Send answer back
        char *answer = "42";
        write(child_to_parent[1], answer, strlen(answer));
        printf("[Child]  Sent answer: \"%s\"\n", answer);

        close(parent_to_child[0]);
        close(child_to_parent[1]);
        exit(0);

    } else {
        // ── PARENT ──
        close(parent_to_child[0]);   // not reading from this
        close(child_to_parent[1]);   // not writing to this

        // Send question
        char *question = "What is 6 x 7?";
        write(parent_to_child[1], question, strlen(question));
        printf("[Parent] Sent question: \"%s\"\n", question);
        close(parent_to_child[1]);

        // Read answer
        char answer[64];
        int n = read(child_to_parent[0], answer, sizeof(answer));
        answer[n] = '\0';
        printf("[Parent] Got answer: \"%s\"\n", answer);

        close(child_to_parent[0]);
        wait(NULL);
    }
}

// ─────────────────────────────────────────
// DEMO 4: Pipe with multiple children
// ─────────────────────────────────────────
void demo_multiple_children() {
    printf("\n=== DEMO 4: Multiple Children Writing to Parent ===\n");

    int fd[2];
    pipe(fd);

    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            // ── CHILD i ──
            close(fd[0]);

            char msg[64];
            snprintf(msg, sizeof(msg), "Message from child %d", i + 1);
            write(fd[1], msg, strlen(msg) + 1);

            close(fd[1]);
            exit(0);
        }
    }

    // ── PARENT ──
    close(fd[1]);   // IMPORTANT: close write end in parent too

    char buf[64];
    int n;
    while ((n = read(fd[0], buf, sizeof(buf))) > 0) {
        printf("[Parent] Got: \"%s\"\n", buf);
    }

    close(fd[0]);
    for (int i = 0; i < 3; i++) wait(NULL);
}

// ─────────────────────────────────────────
// MAIN
// ─────────────────────────────────────────
int main() {
    demo_basic_pipe();
    demo_parent_to_child();
    demo_two_way();
    demo_multiple_children();

    printf("\nDone.\n");
    return 0;
}