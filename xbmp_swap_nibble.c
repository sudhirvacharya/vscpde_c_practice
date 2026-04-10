#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned char var =0xAB;
    unsigned int var1 =0x12345678;
    var = ( (var & 0xF0) >> 4) | ( (var & 0x0F) << 4);
    var1=  (var1 & 0xffff0000  ) >> 16  |   (var1 & 0x00000ffff ) << 16;

    printf(" swap nibble %x \n", var);
    printf(" swap nibble %x \n", var1);

    return 0;
}