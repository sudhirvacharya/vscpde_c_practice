#include <stdio.h>
#include <stdlib.h>

  int a= 0x1234;
  int var= 0x12345678;
  /*
  big endian
  0000 -->12
  0001 -->34

  lil endian
  0000-->34
  0001-->12
  
  */

 char *ptr=&a;

 void convert_endians(  )
 {
    // int var= 0x12345678;
    // 0xFF FF FF FF 
    //  32  24 16 8
    printf("Before conv %x \n", var);
    var = ((var & 0x000000FF) << 24) |  ((var & 0X0000FF00)<< 8 ) | ((var & 0xFF000000)>>24 ) | ( (var & 0x00FF0000) >>8);
    printf("aft conv %x \n", var);


 }
int main()
{
    if(*ptr == (a & 0xff) )
    {
        printf("lil endian: %x \n", *ptr);
    }
    else
    {
         printf("big endian \n");
    }

    //convert endians
    convert_endians();
    return 0;
}