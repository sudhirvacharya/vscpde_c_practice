#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// stack - FILO (First In Last Out)

#define BUFF 8

typedef struct
{
    int data[BUFF];
    // top = -1 means empty, 0 to BUFF-1 are valid positions
    int top;
} stack_t;

stack_t *stack = NULL;

void initstack()
{
    // allocate memory for stack
    stack = malloc(sizeof(stack_t));
    // -1 means stack is empty
    stack->top = -1;
}

void push(int data)
{
    // check if space is available (max index is BUFF-1)
    if (stack->top < BUFF - 1)
    {
        // increment top first, then write
        stack->top++;
        stack->data[stack->top] = data;
    }
    else
    {
        // stack is full, cannot push
        printf("stack is full\n");
    }
}

void pop()
{
    int tmp;
    // check if stack has data (top >= 0 means not empty)
    if (stack->top >= 0)
    {
        // read from top
        tmp = stack->data[stack->top];
        // print popped value
        printf("pop %d\n", tmp);
        // move top down
        stack->top--;
    }
    else
    {
        // stack is empty, nothing to pop
        printf("stack is empty\n");
    }
}

int main()
{
    initstack();
    push(20);   // top=0, data[0]=20
    push(30);   // top=1, data[1]=30
    pop();      // prints: pop 30  (FILO - last in, first out)
    pop();      // prints: pop 20
    return 0;
}