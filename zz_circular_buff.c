#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define BUFF 8

typedef struct
{
    int data[BUFF];
    // head moves forward on every push (write pointer)
    int head;
    // tail moves forward on every pop (read pointer)
    int tail;
    // cnt tracks how many items are currently in the buffer
    int cnt;
} cb_t;

cb_t *cb = NULL;

void initcb()
{
    // allocate memory for the circular buffer
    cb = malloc(sizeof(cb_t));
    // start with empty buffer
    cb->cnt  = 0;
    cb->head = 0;
    cb->tail = 0;
}

void push(int data)
{
    // check if buffer has space before writing
    if (cb->cnt < BUFF)
    {
        // write data at current head position
        cb->data[cb->head] = data;
        // increment item count
        cb->cnt++;
        // move head forward, wrap around to 0 if it reaches BUFF
        cb->head = (cb->head + 1) % BUFF;
    }
    else
    {
        // buffer is full, cannot push
        printf("buf is full\n");
    }
}

void pop()
{
    int tmp;
    // check if buffer has data before reading
    if (cb->cnt > 0)
    {
        // read data from current tail position
        tmp = cb->data[cb->tail];
        // print the popped value
        printf("pop %d\n", tmp);
        // decrement item count
        cb->cnt--;
        // move tail forward, wrap around to 0 if it reaches BUFF
        cb->tail = (cb->tail + 1) % BUFF;
    }
    else
    {
        // buffer is empty, nothing to pop
        printf("buf is empty\n");
    }
}

int main()
{
    // initialize the circular buffer
    initcb();
    // push 20 into buffer  → head=1, cnt=1
    push(20);
    // push 30 into buffer  → head=2, cnt=2
    push(30);
    // pop from buffer → prints 20, tail=1, cnt=1
    pop();
    // pop from buffer → prints 30, tail=2, cnt=0
    pop();

    return 0;
}