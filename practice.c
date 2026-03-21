#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
bool bit;
void bin(unsigned char n)
{

    unsigned char result=0;
    for(int i =7 ; i>=0 ; i--)
    {
        bit |=n >> i ;
        printf( " %d", bit);
    

    }
  
}
int main()
{
    unsigned char n=3;

    bin(n);

    return 0;
}