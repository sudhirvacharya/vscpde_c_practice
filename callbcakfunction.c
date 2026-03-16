#include <stdio.h>
#include <stdlib.h>

void add(int a, int b)
{
    int c=a+b;
    printf("addition :%d \n", c);
}


//(*xyz)(int, int) --> function pointer
void calulcate(int a, int b, void (*xyz)(int, int))
{
    xyz(a,b);

}

int main()
{
    calulcate(3, 2, add);
    return 0;

}