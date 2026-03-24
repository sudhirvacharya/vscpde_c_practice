#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void display_bits(unsigned char n)
{
    for(int i = 7; i >= 0; i--)
    {
        printf("%c", ((n >> i) & 1) ? '1' : '0');
    }
    printf("\n");
}
int main()
{
    
    displaybits(6);



    return 0;
}