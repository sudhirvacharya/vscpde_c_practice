#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

uint32_t next_pow2(uint32_t n) {
    if (n == 0) return 1;
    n--;          // Handle exact powers of 2
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return n + 1;
}
/*

**How it works — trace with `n = 5` (binary `0101`):**
```
n--      → 4       = 0000 0100
n |= n>>1  0000 0100
         | 0000 0010
         = 0000 0110
n |= n>>2  0000 0110
         | 0000 0001
         = 0000 0111
n |= n>>4  0000 0111 (no change, bits already set)
...
n + 1    → 8       = 0000 1000  ✓
*/

//left shift by 1, example 5-> 00101
//16 8 4 2 1
//0  0 0 0 0
//0  0 0 0 1
//0  0 0 1 0
//0  0 1 0 0
//0  1 0 0 0
//1  0 0 0 0
uint32_t next_pow2_loop(uint32_t n) {
    uint32_t p = 1;
    while (p < n)
     p <<= 1;
     
    return p;
}

int main()
{
   printf("%d \n", next_pow2(4));
   printf("%d\n", next_pow2_loop(4));
    return 0;
}
