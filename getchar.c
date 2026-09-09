#include <stdio.h>

int main()
{
    int n, result = 0;

    while ((n = getchar()) != '\n' && n != EOF) {
        if (n < '0' || n > '9') {
            continue; // skip non-digit characters
        }
        result = (result * 10) + (n - '0');
    }

    printf("%d\n", result);

    return 0;
}