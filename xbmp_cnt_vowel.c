#include <stdio.h>
#include <ctype.h>
 
int main()
{
    // Initializing variable.
    char str[100]="india";  
    int i, vowels = 0;

    
    //Initializing for loop. 
    for(i = 0; str[i]; i++)  // loops until the null terminator ('\0') is reached.
    {
        //Counting the vowels.
        if(str[i]=='a'|| str[i]=='e'||str[i]=='i'||
           str[i]=='o'|| str[i]=='u'||str[i]=='A'||
           str[i]=='E'||str[i]=='I'||str[i]=='O' ||str[i]=='U')
        {
            vowels++;
        }
    }
 	
    //Printing the count of vowels.
    printf("Total number of vowels: = %d\n",vowels);
    
    return 0;
}