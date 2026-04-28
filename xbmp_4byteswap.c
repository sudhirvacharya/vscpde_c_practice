#include <stdio.h>
#include <stdint.h>

uint32_t n=0x12345678;
//78563412
int main()
{

  n= ((n & 0x000000ff) << 24)  | (( n & 0x0000ff00 ) <<8) | (( n & 0xff000000 ) >> 24) | (( n & 0x00ff0000 ) >> 8);

  printf("0x%x\n",n);
    
}