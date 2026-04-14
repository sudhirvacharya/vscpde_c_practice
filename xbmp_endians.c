#include <stdio.h>
#include <stdlib.h>

  int a= 0x1234;
  int var= 0x12345678;
  /*
  a = 0x1234 (stored as 4 bytes: 0x00001234)

  Big Endian (MSB at lowest address):
  addr 0x0000 --> 0x00
  addr 0x0001 --> 0x00
  addr 0x0002 --> 0x12
  addr 0x0003 --> 0x34

  Little Endian (LSB at lowest address):
  addr 0x0000 --> 0x34   <-- ptr points here; matches (a & 0x000000FF) = 0x34
  addr 0x0001 --> 0x12
  addr 0x0002 --> 0x00
  addr 0x0003 --> 0x00
  */

 char *ptr = (char *)&a;

 void convert_endians(  )
 {
    /* var = 0x12345678
     * Byte layout (big endian view):
     *  [31:24]   [23:16]   [15:8]    [7:0]
     *   0x12      0x34      0x56      0x78
     *
     * Mask reference:
     *   0xFF000000  -> bits 31:24  (byte 3)
     *   0x00FF0000  -> bits 23:16  (byte 2)
     *   0x0000FF00  -> bits 15:8   (byte 1)
     *   0x000000FF  -> bits  7:0   (byte 0)
     *
     * Swap: byte0<->byte3, byte1<->byte2
     * Result: 0x78563412
     */
    printf("Before conv: 0x%08x \n", var);
    var = ((var & 0x000000FF) << 24) |  /* byte0 -> byte3 */
          ((var & 0x0000FF00) <<  8) |  /* byte1 -> byte2 */
          ((var & 0x00FF0000) >>  8) |  /* byte2 -> byte1 */
          ((var & 0xFF000000) >> 24);   /* byte3 -> byte0 */
    printf("After  conv: 0x%08x \n", var);
 }

int main()
{
    /* Cast to char* to read the lowest address byte.
     * On little endian: lowest addr holds LSB = (a & 0x000000FF) = 0x34
     * On big endian:    lowest addr holds MSB = 0x00, not equal to 0x34
     */
    if(*ptr == (char)(a & 0x000000FF))
    {
        printf("Little endian: lowest addr byte = 0x%x \n", (unsigned char)*ptr);
    }
    else
    {
         printf("Big endian \n");
    }

    //convert endians
    convert_endians();
    return 0;
}