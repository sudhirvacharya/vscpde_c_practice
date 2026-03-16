#include <stdio.h>
#include <stdlib.h>

void add(int a, int b)
{
    int c=a +b ;
    printf("addition: %d \n", c);

}

int main()
{
    add(2,3);
    return 0;
}