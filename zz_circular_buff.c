#include <stdio.h>
#include <stdlib.h>
///RING BUFF
#define MAX_BUF 2

typedef struct
{
    int data[MAX_BUF];
    int head;
    int tail;
    int cnt;
}circular_buff_t;

circular_buff_t *CB=NULL;

void init()
{
    CB = malloc(sizeof(circular_buff_t));
    if (CB == NULL)
    {
        printf("malloc failed\n");
        exit(1);
    }
    CB->head=0;
    CB->tail=0;
    CB->cnt=0;
}

void push(int data)
{
   if (CB->cnt < MAX_BUF)
   {
    CB->data[CB->tail]=data;
    CB->tail= (CB->tail +1) % MAX_BUF;
    CB->cnt++;

    printf("%d pushed data sucess fully \n", data);
   }
   else
   {
    printf(" buf is full \n");
   }
}

void pop()
{
    int data;
    if (CB->cnt > 0)
    {
        data = CB->data[CB->head];
        CB->head = (CB->head+1) % MAX_BUF;
        CB->cnt--;
        printf("%d pop data sucess fully \n", data);
    }
    else
    {
        printf(" buff is empty \n");
    }
}

int main()
{
    init();
    push(10);
    push(20);
    push(30);
    pop();
    pop();
    pop();

    free(CB);
    CB = NULL;

    return 0;
}