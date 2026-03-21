#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool bit;
int main()
{
    int var=170; //1010 1010
    int tmp=0;

    for (int i=7; i >=0 ;i--)
    {
        bit = (var >> i ) & 1 ;
        printf( " %d", bit);

    }

    return 0;
}