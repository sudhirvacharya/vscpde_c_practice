#include <stdio.h>
#include <stdint.h>

int getnum()
{
    int num;
    int value = 0;

    do {
        num = getchar();
        if (num >= '0' && num <= '9') {
            value = value * 10 + (num - '0');
        }
    } while (num != '\n' && num != EOF);

    return value;
}

int main()
{
    printf("dob %d\n", getnum());
    return 0;
}
