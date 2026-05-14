#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>          // ✅ Fix 1: added for malloc

#define STACK_SIZE 5

typedef struct {
    int data[STACK_SIZE];
    int top;
} stack_t;

stack_t *stack = NULL;

void stackinit() {
    stack = malloc(sizeof(stack_t));
    stack->top = -1;
}

int pop() {
    if (stack->top == -1) {  // ✅ Fix 5: underflow guard
        printf("Stack underflow!\n");
        return -1;
    }
   
    int data = stack->data[stack->top];
     stack->top--;
    printf("pop  -> %d\n", data);  // ✅ Fix 2 & 6: semicolon + print value
    return data;
}

void push(int data) {
    if (stack->top == STACK_SIZE - 1) {  // ✅ Fix 4: overflow guard
        printf("Stack overflow!\n");
        return;
    }
    stack->top++;
    stack->data[stack->top] = data;    // ✅ Fix 3: pre-increment
    printf("push -> %d\n", data);        // ✅ Fix 2: semicolon
}

int main() {
    stackinit();
    push(20);
    push(30);
    push(40);
    pop();
    pop();
    free(stack);   // bonus: free allocated memory
    return 0;
}