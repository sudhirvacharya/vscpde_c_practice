#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned char var =0xAB;
    var = ( (var & 0xF0) >> 4) | ( (var & 0x0F) << 4);

    printf(" swap nibble %x \n", var);

    return 0;
}