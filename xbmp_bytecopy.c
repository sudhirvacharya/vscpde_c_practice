#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void copybytes(uint8_t *src, uint8_t *dst, int n)
{
    while(n)
    {
        *dst++=*src++;
        n--;
    }

}

int main()
{

    uint8_t src[5]={1,2,3,4,5};//here size is 5 bytes
    uint8_t dst[5]={0};
    int n= sizeof(src)/sizeof(src[0]);
    copybytes(src, dst, n);
    
   
    return 0;
}