#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
// write queue

//QUEUE IS FIFO -> FIRST IN FIRST OUT

#define BUFF 8
typedef struct 
{
    int data[BUFF];
    int front;
    int rear;
    int cnt;
   
}que_t;
que_t *que =NULL;
 void initque()
 {
    que= malloc(sizeof(que_t));
    que->front=0;
    que->rear=0;
    que->cnt=0;
 }

void enque(int data)
{
    if(que->cnt < BUFF)
    {
        que->data[que->rear]=data;
        que->rear++;
        que->cnt++;
    }
    else
    {
        printf("buff is full");
    }
    
}

void deque()
{

    int tmp;
   if( que->cnt > 0)
   {
    tmp=que->data[que->front];
    printf("deque %d",tmp);
    que->front++;
    que->cnt--;
   }
   else
   printf("que is empty")
}
int main()
{
    initque();
    enque(20);
    enque(30);
    deque();
    deque();

    return 0;
}