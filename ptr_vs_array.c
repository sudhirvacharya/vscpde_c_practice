#include <stdio.h>
#include <stdlib.h>
int *a=NULL;
int main()
{
    a=malloc(sizeof(int));
   
    a[0]=20;
   // a[1]=40;
    //a[2]=60;
    

    printf("%d \n", a[0]);

    return 0;
}

//array
// int a[]={20};
// a[0]=20;
