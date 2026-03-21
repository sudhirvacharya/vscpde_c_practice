#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// xor operation without xor operator
// xor is high when both input are diffrent lvel
//compare both bits and bot diffrent high or low
/*
a b y
00  0
01  1
10  1
11  0
*/

//how to design xor operation
//how we can create xor gate?
// from tt we derive  y=(a' & b ) | (a | b')

bool tmpa, tmpb;
        unsigned char a =3;//0011
    unsigned char b=7;// 0101-->output is 0100
unsigned char tmp;

void xor_oper()
{

    for(int i=7 ; i>=0 ;i--)
    {
        unsigned char tmpa= (a >> i) & 1;
        unsigned char tmpb= (b >> i) & 1;

        if( tmpa   != tmpb)
        {
            tmp |= 1 << i;
        }
       
    }
    printf(" xor operation %d \n",tmp);
}
int main()
{
   // xor_oper();
    // XOR = A'B + AB'
    tmp = (~a & b) | (a & ~b);
     printf(" xor operation %d \n",tmp);


    return 0;
}