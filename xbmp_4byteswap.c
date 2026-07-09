#include <stdio.h>
#include <stdint.h>

uint32_t n=0x12345678;
//78563412
int main()
{

#include <stdint.h>

// 4-byte full swap: 0x12345678 -> 0x78563412 (bytes: 78 56 34 12)
uint32_t n1 = 0x12345678;
n1 = ((n1 & 0x000000FF) << 24) |
     ((n1 & 0x0000FF00) << 8)  |
     ((n1 & 0x00FF0000) >> 8)  |
     ((n1 & 0xFF000000) >> 24);

// 4-byte outer-pair swap: 0x12345678 -> 0x78561234 (bytes: 78 56 12 34)
uint32_t n2 = 0x12345678;
n2 = ((n2 & 0x000000FF) << 24) |
     ((n2 & 0x0000FF00) << 8)  |
     ((n2 & 0x00FF0000) >> 16) |
     ((n2 & 0xFF000000) >> 16);

// 2-byte swap: 0x1234 -> 0x3412
uint16_t n3 = 0x1234;
n3 = ((n3 & 0x00FF) << 8) | ((n3 & 0xFF00) >> 8);

// 2-byte swap + nibble twist: 0x1234 -> 0x3421
uint16_t n4 = 0x1234;
n4 = ((n4 & 0x00FF) << 8) | ((n4 & 0x0F00) >> 4) | ((n4 & 0xF000) >> 12);

// nibble swap (single byte): 0x12 -> 0x21
uint8_t n5 = 0x12;
n5 = ((n5 & 0x0F) << 4) | ((n5 & 0xF0) >> 4);
    
}