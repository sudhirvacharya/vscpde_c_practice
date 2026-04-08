#include <stdio.h>

int main() {
    int n=9, i;
    long long a = 0, b = 1, next;


    printf("Fibonacci Series: ");
    for (i = 1; i <= n; i++) {
        printf("%lld ", a);
        next = a + b;
        a = b;
        b = next;
    }

    return 0;
}