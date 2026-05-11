// ┌─────────────────────────────────────────────────────┐
// │  lo_fifo.c — Named Pipes (FIFO)                     │
// │  Compile : gcc -o lo_fifo lo_fifo.c                 │
// │  Run     : ./lo_fifo                                 │
// │  Clean   : rm -f /tmp/lo_fifo_test /tmp/lo_fifo_A   │
// │            rm -f /tmp/lo_fifo_B                      │
// └─────────────────────────────────────────────────────┘

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define FIFO_PATH "/tmp/lo_fifo_test"

// ─────────────────────────────────────────
// DEMO 1: Basic FIFO
// child  → writes
// parent → reads
// ─────────────────────────────────────────
void demo_basic_fifo() {
    printf("\n=== DEMO 1: Basic FIFO (child writes, parent reads) ===\n");

    // Step 1: create FIFO file in filesystem
    mkfifo(FIFO_PATH, 0666);

    pid_t pid = fork();

    if (pid == 0) {
        // ── CHILD: Writer ──
        // open() BLOCKS here until parent opens read end
        int fd = open(FIFO_PATH, O_WRONLY);

        char *msg = "Hello via FIFO!";
        write(fd, msg, strlen(msg) + 1);    // +1 sends '\0' too
        printf("[Child]  Sent: \"%s\"\n", msg);

        close(fd);
        exit(0);

    } else {
        // ── PARENT: Reader ──
        // open() BLOCKS here until child opens write end
        int fd = open(FIFO_PATH, O_RDONLY);

        char buf[64];
        int n = read(fd, buf, sizeof(buf));
        buf[n] = '\0';
        printf("[Parent] Received: \"%s\"\n", buf);

        close(fd);
        wait(NULL);
        unlink(FIFO_PATH);   // Step 2: delete FIFO from filesystem
    }
}

// ─────────────────────────────────────────
// DEMO 2: Multiple messages through FIFO
// read() returns 0 (EOF) when writer closes fd
// ─────────────────────────────────────────
void demo_multiple_messages() {
    printf("\n=== DEMO 2: Multiple Messages + EOF Detection ===\n");

    mkfifo(FIFO_PATH, 0666);

    pid_t pid = fork();

    if (pid == 0) {
        // ── CHILD: Writer ──
        int fd = open(FIFO_PATH, O_WRONLY);

        char *messages[] = {"First", "Second", "Third", "Fourth"};
        for (int i = 0; i < 4; i++) {
            write(fd, messages[i], strlen(messages[i]) + 1);
            printf("[Writer] Sent: \"%s\"\n", messages[i]);
            sleep(1);   // simulate delay
        }

        close(fd);      // closing write-end → reader gets EOF
        exit(0);

    } else {
        // ── PARENT: Reader ──
        int fd = open(FIFO_PATH, O_RDONLY);

        char buf[64];
        int n;
        // read() returns 0 when all writers have closed
        while ((n = read(fd, buf, sizeof(buf))) > 0) {
            buf[n] = '\0';
            printf("[Reader] Received: \"%s\"\n", buf);
        }
        printf("[Reader] EOF — writer closed the FIFO\n");

        close(fd);
        wait(NULL);
        unlink(FIFO_PATH);
    }
}

// ─────────────────────────────────────────
// DEMO 3: Non-blocking open (O_NONBLOCK)
// Does NOT wait for the other side to connect
// ─────────────────────────────────────────
void demo_nonblocking() {
    printf("\n=== DEMO 3: Non-Blocking Open ===\n");

    mkfifo(FIFO_PATH, 0666);

    // Without O_NONBLOCK → would block forever (no writer)
    // With    O_NONBLOCK → returns immediately
    int fd = open(FIFO_PATH, O_RDONLY | O_NONBLOCK);
    if (fd == -1) {
        perror("open");
        unlink(FIFO_PATH);
        return;
    }

    printf("[Reader] Opened FIFO (no writer yet)\n");

    char buf[64];
    int n = read(fd, buf, sizeof(buf));

    if (n == -1)
        // EAGAIN = no data right now, try again later (not a real error)
        printf("[Reader] No data yet (EAGAIN) — would retry in real code\n");
    else if (n == 0)
        printf("[Reader] EOF\n");
    else
        printf("[Reader] Got: %.*s\n", n, buf);

    close(fd);
    unlink(FIFO_PATH);
}

// ─────────────────────────────────────────
// DEMO 4: Two-way communication
// Needs TWO FIFOs (one per direction)
// FIFO_A: parent → child
// FIFO_B: child  → parent
// ─────────────────────────────────────────
#define FIFO_A "/tmp/lo_fifo_A"
#define FIFO_B "/tmp/lo_fifo_B"

void demo_two_way() {
    printf("\n=== DEMO 4: Two-Way Communication (2 FIFOs) ===\n");

    mkfifo(FIFO_A, 0666);
    mkfifo(FIFO_B, 0666);

    pid_t pid = fork();

    if (pid == 0) {
        // ── CHILD ──
        int in  = open(FIFO_A, O_RDONLY);   // read from parent
        int out = open(FIFO_B, O_WRONLY);   // write to parent

        char question[64];
        int n = read(in, question, sizeof(question));
        question[n] = '\0';
        printf("[Child]  Got question : \"%s\"\n", question);

        char *answer = "The answer is 42";
        write(out, answer, strlen(answer) + 1);
        printf("[Child]  Sent answer  : \"%s\"\n", answer);

        close(in);
        close(out);
        exit(0);

    } else {
        // ── PARENT ──
        int out = open(FIFO_A, O_WRONLY);   // write to child
        int in  = open(FIFO_B, O_RDONLY);   // read from child

        char *question = "What is 6 x 7?";
        write(out, question, strlen(question) + 1);
        printf("[Parent] Sent question : \"%s\"\n", question);
        close(out);

        char answer[64];
        int n = read(in, answer, sizeof(answer));
        answer[n] = '\0';
        printf("[Parent] Got answer    : \"%s\"\n", answer);

        close(in);
        wait(NULL);
        unlink(FIFO_A);
        unlink(FIFO_B);
    }
}

// ─────────────────────────────────────────
// MAIN
// ─────────────────────────────────────────
int main() {
    demo_basic_fifo();
    demo_multiple_messages();
    demo_nonblocking();
    demo_two_way();
    printf("\nAll FIFO demos done.\n");
    return 0;
}

/**
 * 
 * 
 * 
 * Explanation — Demo by Demo
Demo 1 — Basic FIFO
mkfifo() creates a file in /tmp
child  → open(O_WRONLY) BLOCKS until parent opens read end
parent → open(O_RDONLY) BLOCKS until child opens write end
         ↑ both unblock together (rendezvous point)

Demo 2 — Multiple Messages
writer sends 4 messages one by one (sleep 1s between)
reader loops: while(read() > 0) → print
writer calls close(fd) → reader gets EOF (read returns 0)

Demo 3 — Non-Blocking
O_RDONLY | O_NONBLOCK → open returns immediately, no waiting
read() with no writer → returns -1 with errno = EAGAIN
used in servers that poll multiple FIFOs without hanging
Demo 4 — Two-Way
ONE FIFO can only go one direction at a time
So two-way needs TWO FIFOs:
  FIFO_A → parent writes, child reads
  FIFO_B → child writes, parent reads

Key Rules to Remember 📌
RuleWhyopen() blocks until both sides connectFIFO needs a reader AND writerread()
 returns 0 = EOF
 writer closed their endunlink() after done
 FIFO file stays in /tmp forever otherwise
 Two-way = two FIFOsSingle FIFO is one-directional
 */

 /*
 
 gcc -o lo_fifo lo_fifo.c    # compile
./lo_fifo                    # run
rm -f /tmp/lo_fifo_test /tmp/lo_fifo_A /tmp/lo_fifo_B   # cleanup if needed
 */