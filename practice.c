#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
// ciruclar buffer

//fifo first in first out
#define BUFF 8
typedef struct
{
    int data[BUFF];
    int head;
    int tail;
    int cnt;
}cb_t;

cb_t *cb=NULL;

void initcb()
{
    cb= malloc(sizeof(cb_t));
    cb->cnt=0;
    cb->head=0;
    cb->tail=0;
}
void push(int data)
{
    if(cb->cnt < BUFF)
    {


    cb->data[cb->head]=data;
    cb->cnt++;
    cb->head= (cb->head +1) % BUFF;
    }
    else
    {

        printf( buf is full)
    }

}
void pop()
{
    int tmp;
    if(cb->cnt > 0)
    {
   tmp= cb->data[cb->tail];
    cb->cnt--;
    cb->tail =(cb->tail +1) % BUFF;
    }
    else
    prinf(buf i sempty)

}
int main()
{
    initcb();
    push(20);
    pushs(30);
    pop();
    pop();


    return 0;
}

