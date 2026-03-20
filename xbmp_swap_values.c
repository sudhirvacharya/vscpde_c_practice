#include <stdio.h>
#include <stdlib.h>
void swap(int a, int b)
{
    a ^=b;
    b ^=  a;
    a ^= b;
     printf("aft swap: \n %d \n %d \n", a, b);

}
int main()
{

    int a=2, b=5;
    printf("before swap: \n %d \n %d \n", a, b);
    swap(a, b);


}