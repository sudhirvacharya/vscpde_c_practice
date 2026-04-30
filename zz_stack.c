#include <stdio.h>
#include <stdint.h>

#define STACK_SIZE 5

// Stack structure
typedef struct {
    int data[STACK_SIZE];
    int top;
} Stack;

// Initialize stack
void stack_init(Stack *s) {
    s->top = -1;        // empty stack = -1
}

// Check if stack is full
int is_full(Stack *s) {
    return s->top == STACK_SIZE - 1;
}

// Check if stack is empty
int is_empty(Stack *s) {
    return s->top == -1;
}

// Push - add element to TOP
void push(Stack *s, int val) {
    if (is_full(s)) {
        printf("Stack OVERFLOW! Cannot push %d\n", val);
        return;
    }
    s->top++;
    s->data[s->top] = val;
    printf("Pushed: %d\n", val);
}

// Pop - remove element from TOP
int pop(Stack *s) {
    if (is_empty(s)) {
        printf("Stack UNDERFLOW! Nothing to pop\n");
        return -1;
    }
    int val = s->data[s->top];
    s->top--;
    printf("Popped: %d\n", val);
    return val;
}

// Peek - see TOP element without removing
int peek(Stack *s) {
    if (is_empty(s)) {
        printf("Stack is EMPTY!\n");
        return -1;
    }
    return s->data[s->top];
}

// Print stack
void print_stack(Stack *s) {
    if (is_empty(s)) {
        printf("Stack is EMPTY!\n");
        return;
    }
    printf("Stack (top -> bottom): ");
    for (int i = s->top; i >= 0; i--) {
        printf("%d ", s->data[i]);
    }
    printf("\n");
}

int main(void) {
    Stack s;
    stack_init(&s);

    // Push elements
    push(&s, 10);
    push(&s, 20);
    push(&s, 30);
    push(&s, 40);
    push(&s, 50);

    // Try pushing when full
    push(&s, 60);

    // Print stack
    print_stack(&s);

    // Peek top
    printf("Top element: %d\n", peek(&s));

    // Pop elements
    pop(&s);
    pop(&s);

    // Print after pop
    print_stack(&s);

    // Push again
    push(&s, 60);
    push(&s, 70);

    print_stack(&s);

    return 0;
}