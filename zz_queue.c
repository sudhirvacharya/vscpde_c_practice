#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/* ============================================================
 *  CIRCULAR QUEUE  (FIFO - First In First Out)
 * ============================================================
 *
 *  WHY CIRCULAR?
 *  -------------
 *  In a linear queue, once rear reaches BUFF it stops,
 *  even if front has moved forward and slots are free.
 *
 *  Circular queue fixes this by wrapping rear back to 0
 *  using the modulo (%) operator.
 *
 *  HOW % BUFF WORKS  (BUFF = 8):
 *  --------------------------------
 *  que->rear | que->rear + 1 | % 8 | Result
 *  ----------|---------------|-----|-------
 *      0     |       1       | 1%8 |   1
 *      1     |       2       | 2%8 |   2
 *      2     |       3       | 3%8 |   3
 *      3     |       4       | 4%8 |   4
 *      4     |       5       | 5%8 |   5
 *      5     |       6       | 6%8 |   6
 *      6     |       7       | 7%8 |   7
 *      7     |       8       | 8%8 |   0  <-- wraps back to start!
 *
 *  So instead of stopping at index 7, rear goes back to 0
 *  and reuses freed slots. Same logic applies to front.
 *
 *  VISUAL:
 *          [0]
 *      [7]     [1]
 *    [6]           [2]
 *      [5]     [3]
 *          [4]
 *
 *  rear keeps moving around the circle forever.
 * ============================================================ */

#define BUFF 8

typedef struct
{
    int data[BUFF];
    int front;  /* index of next item to dequeue */
    int rear;   /* index where next item will be enqueued */
    int cnt;    /* number of items currently in queue */
} que_t;

que_t *que = NULL;

/* ------------------------------------------------------------
 * initque: allocate memory and reset queue to empty state
 * ------------------------------------------------------------ */
void initque()
{
    que = malloc(sizeof(que_t));
    que->front = 0;
    que->rear  = 0;
    que->cnt   = 0;  /* 0 = empty, BUFF = full */
}

/* ------------------------------------------------------------
 * enque: add item to rear of queue
 *
 *  rear = (rear + 1) % BUFF  -- moves rear forward, wraps at 7->0
 * ------------------------------------------------------------ */
void enque(int data)
{
    if (que->cnt < BUFF)               /* queue not full? */
    {
        que->data[que->rear] = data;
        que->rear = (que->rear + 1) % BUFF;  /* circular wrap */
        que->cnt++;
    }
    else
    {
        printf("buff is full\n");
    }
}

/* ------------------------------------------------------------
 * deque: remove item from front of queue
 *
 *  front = (front + 1) % BUFF  -- moves front forward, wraps at 7->0
 * ------------------------------------------------------------ */
void deque()
{
    if (que->cnt > 0)                  /* queue not empty? */
    {
        int tmp = que->data[que->front];
        printf("deque %d\n", tmp);
        que->front = (que->front + 1) % BUFF;  /* circular wrap */
        que->cnt--;
    }
    else
    {
        printf("que is empty\n");
    }
}

int main()
{
    initque();
    enque(20);
    enque(30);
    deque();        /* prints: deque 20 */
    deque();        /* prints: deque 30 */
    deque();        /* prints: que is empty */

    return 0;
}