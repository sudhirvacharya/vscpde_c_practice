
#include <stdio.h>
#include <stdlib.h>

int main()
{

    int arr[] = {10, 20, 30};
    int *ptr = arr;

    (*(ptr + 1))++;/// here value is incremnting
    ///*(ptr + 1)++; its invalid and dot write like this

    *ptr++;//here addres increment

    printf("%d", arr[1]);   // 21
    return 0;
}