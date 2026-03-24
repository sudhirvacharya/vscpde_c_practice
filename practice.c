#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BIT 8

int main()
{
    unsigned char var=1;
   unsigned char  tmp= ( var >> 1 ) | ( var << (BIT -1));
   printf(" tmp: %x", tmp);


    return 0;
}