#include <stdio.h>
#include <stdlib.h>

void add(int a, int b)
{
    int c= a+b;
    printf("addition %d \n", c);
}
void sub(int a, int b)
{
    int c= a-b;
    printf("sub %d\n", c);
}
int main()
{
    void (*ptr)(int, int) = add;
    ptr = add;
    ptr(3,2);

    return 0;

}