#include <stdio.h>
#include <stdint.h>
//convert upper case vice versa

int main()
{
    char str[]="INDIA";
    int n=6;
    
    for(int i=0; i<n; i++)
    {
        str[i]= str[i] + ( 'a' -'A');//convert lower case
       // str[i]= str[i] + ( 'a' -'A');//convert uppr case
    }

   printf("%s\n",str);
    
    printf("%d\n%d",'a','A');


    return 0;
}