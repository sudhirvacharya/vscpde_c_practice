#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

/*find size of data types without size of operator*/
int main()
{

    int array[2]={2,3};// 0,1 index
    int *ptr1=&array[0];
    int *ptr2=&array[1];
    ptrdiff_t diff = (char*)ptr2 - (char*)ptr1;
    printf("size of int: %td\n", diff);
    
}