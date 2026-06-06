#include <stdio.h>

// Default_Handler — fallback infinite loop
void Default_Handler(void) 
{
    printf("Default_Handler called — unhandled interrupt!\n");
    while (1);
}

// SysTick_Handler — weak alias pointing to Default_Handler
// same as .weak + .thumb_set in startup.s
void SysTick_Handler(void) __attribute__((weak, alias("Default_Handler")));

// uncomment below to test strong override

void SysTick_Handler(void)
{
    printf("YOUR SysTick_Handler called — strong symbol!\n");
}


int main(void)
{

    SysTick_Handler();   // simulate interrupt firing
    return 0;
}