#include <stdio.h>
#include <stdlib.h>

#define SETBIT(N, POS) ( N |= 1<< POS )
#define CLEABIT(N, POS) ( N &= ~( 1 <<POS ) )
#define TOGGLE(N, POS) ( N ^=( 1 <<POS ))
#define IS_BIT_SET(n, pos) ((n) & (1U << (pos)))

int main()
{
    int a=0;
    int b=1;
    int c=1;
        int d=1;

    printf("SETBIT %d \n", SETBIT(a, 0));
    printf("CLEABIT %d \n", CLEABIT(b, 0));
    printf("TOGGLE %d \n", TOGGLE(c, 0));
    printf(" is bit set" %d \n",  IS_BIT_SET(d, 0));

    return 0;
}