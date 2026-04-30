#include <stdio.h>
#include <stdint.h>

#define QUEUE_SIZE 5

// Queue structure
typedef struct {
    int data[QUEUE_SIZE];
    int front;
    int rear;
    int count;
} Queue;

// Initialize queue
void queue_init(Queue *q) {
    q->front = 0;
    q->rear  = 0;
    q->count = 0;
}

// Check if queue is full
int is_full(Queue *q) {
    return q->count == QUEUE_SIZE;
}

// Check if queue is empty
int is_empty(Queue *q) {
    return q->count == 0;
}

// Add element to rear
void enqueue(Queue *q, int value) {
    if (is_full(q)) {
        printf("Queue is FULL! Cannot add %d\n", value);
        return;
    }
    q->data[q->rear] = value;
    q->rear  = (q->rear + 1) % QUEUE_SIZE;
    q->count++;
    printf("Enqueued: %d\n", value);
}

// Remove element from front
int dequeue(Queue *q) {
    if (is_empty(q)) {
        printf("Queue is EMPTY!\n");
        return -1;
    }
    int value = q->data[q->front];
    q->front = (q->front + 1) % QUEUE_SIZE;
    q->count--;
    printf("Dequeued: %d\n", value);
    return value;
}

// Peek front element
int peek(Queue *q) {
    if (is_empty(q)) {
        printf("Queue is EMPTY!\n");
        return -1;
    }
    return q->data[q->front];
}

// Print all elements
void print_queue(Queue *q) {
    if (is_empty(q)) {
        printf("Queue is EMPTY!\n");
        return;
    }
    printf("Queue: ");
    for (int i = 0; i < q->count; i++) {
        int idx = (q->front + i) % QUEUE_SIZE;
        printf("%d ", q->data[idx]);
    }
    printf("\n");
}

int main(void) {
    Queue q;
    queue_init(&q);

    // Add elements
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);
    enqueue(&q, 50);

    // Try adding when full
    enqueue(&q, 60);

    // Print queue
    print_queue(&q);

    // Peek front
    printf("Front element: %d\n", peek(&q));

    // Remove elements
    dequeue(&q);
    dequeue(&q);

    // Print after dequeue
    print_queue(&q);

    // Add more after dequeue
    enqueue(&q, 60);
    enqueue(&q, 70);

    print_queue(&q);

    return 0;
}