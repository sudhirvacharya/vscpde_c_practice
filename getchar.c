#include <stdio.h>
#include <stdlib.h>
   int tmp, num;
int getnum()
{
     do
    {
        num= getchar();   // waits for a character input
        if(num >= '0' && num <= '9')
        {
            //converting ascii to decimal
            // *10 will left shift decimal digit, 
            tmp=(tmp*10) + (num - 0x30);
        }
    
    }
    while (num != '\n' && num != EOF);  // stop at newline or EOF

    return tmp;
}

int main()
{
    printf("dob is: %d \n", getnum());

    return 0;
}