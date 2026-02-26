#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int a;
    int b;

}__attribute__((packed)) reg1;

int main(void)
{
    reg1 *gpio= malloc(sizeof(reg1));
   gpio->a=1;

    printf("hello \n");
}