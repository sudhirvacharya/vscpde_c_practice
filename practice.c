#include <stdio.h>
int add(int a, int b)

//__forceinline int add(int a, int b)
{
    return a + b;
}

int main()
{
    int sum1 = add(2, 5);
    int sum2 = add(2, 5);

    printf("%d %d\n", sum1, sum2);
    return 0;
}