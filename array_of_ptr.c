#include <stdio.h>

int main() {
    int a = 10, b = 20, c = 30;
    int array[]={1,2,3,4};
    int *ptr[3];   // array of 3 int pointers

    ptr[0] = &a;
    ptr[1] = &b;
    ptr[2] = &c;

    for(int i=0; i<3; i++) {
        printf("Value at arr[%d] = %d\n", i, *ptr[i]);
    }

    for (int i=0;i<3 ;i++)
    {
        ptr[i]=&array[i]
           printf("Value at arr[%d] = %d\n", i, *ptr[i]);
    }


    return 0;
}
