#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define BUF_SIZE 8

typedef struct {
    uint8_t  data[BUF_SIZE];
    uint32_t head;    /* write index (push) */
    uint32_t tail;    /* read index  (pop)  */
    uint32_t count;
} CircBuf_t;

void cb_init(CircBuf_t *cb)
{
    cb->head  = 0;
    cb->tail  = 0;
    cb->count = 0;
}

/* push: write at head, overwrite oldest if full */
void cb_push(CircBuf_t *cb, uint8_t byte)
{
    cb->data[cb->head] = byte;
    cb->head = (cb->head + 1) % BUF_SIZE;

    if (cb->count == BUF_SIZE) {
        /* full: advance tail, oldest byte lost */
        cb->tail = (cb->tail + 1) % BUF_SIZE;
    } else {
        cb->count++;
    }
}

/* pop: read from tail */
bool cb_pop(CircBuf_t *cb, uint8_t *out)
{
    if (cb->count == 0) {
        return false;
    }
    *out = cb->data[cb->tail];
    cb->tail  = (cb->tail + 1) % BUF_SIZE;
    cb->count--;
    return true;
}

int main(void)
{
    CircBuf_t cb;
    uint8_t   val;

    cb_init(&cb);

    /* push 10 bytes into size-8 buf -> bytes 1,2 overwritten */
    for (uint8_t i = 1; i <= 10; i++) {
        cb_push(&cb, i);
        printf("push %2d | count=%u\n", i, cb.count);
    }

    printf("\n--- pop ---\n");
    while (cb_pop(&cb, &val)) {
        printf("pop: %d\n", val);
    }

    return 0;
}