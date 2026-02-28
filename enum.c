#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    SUN,
    MON,
    TUE,
}WEEKDAY;

int main(void)
{

    WEEKDAY today;

    today=TUE;
    printf("today:%d \n", today);

    return 0;
}

