#include <stdio.h>

int main()
{
    unsigned int n=0xaa;
    //// take odd  bits, shift right 0xaa
    //  // take even bits, shift left 0x55
    n = (n & 0xaaaaaaaa) >> 1 | (n & 0x55555555);
    printf("%x \n", n);

    return 0;
}