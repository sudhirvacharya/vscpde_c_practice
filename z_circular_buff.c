#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFF 6

typedef struct
{
    char data[MAX_BUFF];
    int  head;
    int  tail;
    int  count;
} ring_buff;

ring_buff *rb = NULL;

void enqueue(char tmp)
{
    if (rb->count == MAX_BUFF)
    {
        printf("buffer full, drop %d\n", tmp);
        return;
    }

    rb->data[rb->head] = tmp;
    printf("enqueue: %d at head: %d\n", rb->data[rb->head], rb->head);
    rb->head = (rb->head + 1) % MAX_BUFF;
    rb->count++;
}

void dequeue(void)
{
    char tmp;

    if (rb->count == 0)
    {
        printf("buffer empty\n");
        return;
    }

    tmp = rb->data[rb->tail];
    printf("dequeue: %d from tail: %d\n", tmp, rb->tail);
    rb->tail = (rb->tail + 1) % MAX_BUFF;
    rb->count--;
}

int is_full(void)
{
    return rb->count == MAX_BUFF;
}

int is_empty(void)
{
    return rb->count == 0;
}

void print_buffer(void)
{
    int i;
    int idx;

    if (is_empty())
    {
        printf("buffer empty\n");
        return;
    }

    printf("buffer [count=%d]: ", rb->count);
    for (i = 0; i < rb->count; i++)
    {
        idx = (rb->tail + i) % MAX_BUFF;
        printf("%d ", rb->data[idx]);
    }
    printf("\n");
}

int main(void)
{
    rb = malloc(sizeof(ring_buff));
    rb->head  = 0;
    rb->tail  = 0;
    rb->count = 0;

    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    enqueue(50);
    enqueue(60);
    enqueue(70);    /* buffer full — dropped */

    print_buffer();

    dequeue();
    dequeue();

    print_buffer();

    enqueue(70);
    enqueue(80);

    print_buffer();

    free(rb);
    return 0;
}