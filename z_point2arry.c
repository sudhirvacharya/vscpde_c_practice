#include <stdio.h>

int main() {
    int arr[5] = {10, 20, 30, 40, 50};

    // ptr is a pointer to an array of 5 ints
    int (*ptr)[5] = &arr;

    printf("Array address : %p\n", ptr);
    printf("First element : %d\n", (*ptr)[0]);
    printf("Third element : %d\n", (*ptr)[2]);

    // Traversing using pointer to array
    for (int i = 0; i < 5; i++) {
        printf("(*ptr)[%d] = %d\n", i, (*ptr)[i]);
    }

    return 0;
}