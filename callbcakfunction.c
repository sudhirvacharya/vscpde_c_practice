#include <stdio.h>
#include <stdlib.h>
int result;
int *add(int a, int b)
{
    result=a+b;
  
    return &result;
}


//(*xyz)(int, int) --> function pointer
void calulcate(int a, int b, int* (*xyz)(int, int))
{
    int tmp;
    tmp=*xyz(a,b);
    printf("addition :%d \n", tmp);

}

int main()
{
    calulcate(3, 2, add);
    return 0;

}