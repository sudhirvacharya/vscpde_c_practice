#include <stdio.h>
#include <stdint.h>

uint16_t n=0x1234;
//3412
int main()
{

  n= ((n & 0x00ff) << 8)  | (( n & 0xff00 )>> 8);

  printf("0x%x\n",n);
    
}