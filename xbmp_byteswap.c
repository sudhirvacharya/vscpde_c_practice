#include <stdio.h>
#include <stdint.h>

uint8_t n=0x12;
int main()
{

  n= ((n & 0x0f) << 4)  | (( n & 0xf0 )>> 4);

  printf("0x%x\n",n);
    
}