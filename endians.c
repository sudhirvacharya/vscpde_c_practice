#include <stdio.h>
#include <stdlib.h>

  int a= 0x1234;
  /*
  big endian
  0000 -->12
  0001 -->34

  lil endian
  0000-->34
  0001-->12
  
  */

 char *ptr=&a;

int main()
{
    if(*ptr == (a & 0xff) )
    {
        printf("lil endian: %x", *ptr);
    }
    else
    {
         printf("big endian");
    }
    return 0;
}