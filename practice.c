#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//print binary

void reverse_str(char *a)
{
    if(*a != '\0')
    {
        reverse_str(a+1);
        putchar(*a);
        fflush(stdout);
    }

}

#define bit 8

int main()
{
    /*

    //int a[]={3,4,6,7};
    char a[]="india";
    int n= sizeof(a)/sizeof(a[0]);
    reverse_str(a);

    for(int i=0 ; i<n ; i++)
    {
        printf("%d",a[i]);
    } */
   // rotate right 
    uint8_t n=1;// 0000 0000
    uint8_t r =2;
    n= (n>> 2) | ( n << (bit -2));
    printf("%d\n",n);
    00000001



    return 0;

}