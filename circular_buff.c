#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFF 6
typedef struct
{
    char data[MAX_BUFF];
    int head;
    int tail;

}circular_buff;

circular_buff *cb=NULL;
void produce(char tmp)
{
    if (cb->head->==MAX_BUFF )
        cb->head=0;

    cb->data[cb->head]=tmp;
    printf("produce data %d \n", cb->data[cb->head]);
    cb->head++;
   

}

void consume()
{
    char tmp;
   if( cb->tail==MAX_BUFF)
            cb->tail=0;

    tmp=cb->data[cb->tail];
    printf("tail: %d \n", cb->tail);
    cb->tail++;

}
int main(void)
{
    cb=malloc(sizeof(circular_buff));
    produce(20);
    produce(30);
    produce(20);
    consume();
    consume();



}