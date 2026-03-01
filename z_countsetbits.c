#include <stdio.h>
#include <stdlib.h>


// 8421
// 0101
// 0100
// 0011
// 0010
// 0001
// 0000

int main()
{
    int var =5, cnt=0;
    while(var)
    {
        var = var & (var -1);
        cnt++;
        printf("var:%b \n", var);
    }
    printf("total count:%d \n", cnt);
}