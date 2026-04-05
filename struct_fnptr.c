#include <stdio.h>

//how to use function inside structure

void add (int x, int y)
{

    printf("c:%d \n", x+y);
    
}

typedef struct
{
    int data;
    void (*fnptr)(int, int);
}test;

test t;

int main()
{
    t.fnptr=add;
    t.fnptr(4, 4);
    

}

