
// union is a userdefined data types that allows multiple member
// with poeencially diffrent data types, to share the same memory


#include <stdio.h>

typedef union {
    char a[4];
    int i_num;
} Number;


//strucure inside unioin and also using bitf

typedef struct regb
{
    unsigned int setbit:1;
    unsigned int overflow:31;
}structb;

typedef union{
    unsigned int reg;
    structb bits;
}unionreg;

unionreg gpio;

int main()
{
    gpio.reg=0xffff;
    printf("setbit : %d \n", gpio.bits.setbit);
}

