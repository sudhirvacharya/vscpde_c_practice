#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a=2, b=5, c=0, max;

    (a>b)? (c=10):(c=20); 
    max= ( a > b) ? a:b;
    max = (a > b) ? ((a > c) ? a : c) : ((b > c) ? 5 : 7);
    


    printf("c:%d \n",c);

    return 0;
}