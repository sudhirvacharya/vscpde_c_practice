#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//strip lowet bit example 1100
//                         ^
// 12 -11 = 1100 - 1011 --> here lowest bit got cleared.
/*
1100

&

1011
1000 <----ans
*/
bool b;

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
    unsigned char n=12;//0000 1100
    printf("before \n");
    display_bits(n);
    n=n & (n-1);
      printf("aft \n");
    display_bits(n);
     printf("\n");




    return 0;
}
