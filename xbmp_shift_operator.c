#include <stdio.h>
#include <stdlib.h>

int main()
{
    // basic shifts
    printf("1 << 0 = %d\n", 1 << 0);   // 1
    printf("1 << 1 = %d\n", 1 << 1);   // 2
    printf("1 << 2 = %d\n", 1 << 2);   // 4
    printf("1 << 3 = %d\n", 1 << 3);   // 8

    // tricky 1 — people forget shift multiplies/divides by 2
    printf("\n-- tricky: shift = multiply/divide by 2 --\n");
    printf("5 << 1 = %d\n", 5 << 1);   // 5 * 2 = 10
    printf("5 << 2 = %d\n", 5 << 2);   // 5 * 4 = 20
    printf("8 >> 1 = %d\n", 8 >> 1);   // 8 / 2 = 4
    printf("8 >> 2 = %d\n", 8 >> 2);   // 8 / 4 = 2

    // tricky 2 — shifting by 0 does nothing
    printf("\n-- tricky: shift by 0 --\n");
    printf("7 << 0 = %d\n", 7 << 0);   // still 7

    // tricky 3 — OR sets a bit, AND checks a bit
    printf("\n-- tricky: set vs check bit --\n");
    unsigned char reg = 0;
    reg |= (1 << 3);                    // SET bit 3
    printf("after set  bit3 = %d\n", reg);       // 8

    if(reg & (1 << 3))                  // CHECK bit 3
        printf("bit 3 is SET\n");

    reg &= ~(1 << 3);                   // CLEAR bit 3
    printf("after clear bit3 = %d\n", reg);      // 0

    // tricky 4 — ~ on small variable promotes to int!
    printf("\n-- tricky: ~ on unsigned char --\n");
    unsigned char a = 1;
    printf("~a = %d\n", ~a);            // NOT 254! prints -2 due to int promotion
    printf("~a & 0xFF = %d\n", ~a & 0xFF);  // correct way = 254

    // tricky 5 — shifting negative number is undefined behavior
    printf("\n-- tricky: never shift negative --\n");
    int x = -1;
    // x << 1  — undefined behavior! never do this
    printf("always use unsigned for shifts\n");

    return 0;
}