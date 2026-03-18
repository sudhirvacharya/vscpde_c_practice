#include <stdio.h>
#include <stdlib.h>

void  reverse_string(char *str, char size)
{
    char tmp;
    char start=0;
    char end = size-1;
    while(start < end)
    {
        tmp=str[start];
        str[start]=str[end];
        str[end]=tmp;
        start++;
        end--;
    }
}

void  reverse_string1(char *str, char size)
{
    /*
    Iteration 1:  str[5-1] = str[4] = 'a'  → prints 'a',  size becomes 4
    Iteration 2:  str[4-1] = str[3] = 'i'  → prints 'i',  size becomes 3
    Iteration 3:  str[3-1] = str[2] = 'd'  → prints 'd',  size becomes 2
    Iteration 4:  str[2-1] = str[1] = 'n'  → prints 'n',  size becomes 1
    Iteration 5:  str[1-1] = str[0] = 'i'  → prints 'i',  size becomes 0
    */
    while(size)
    {
        putchar(str[size-1]);
        fflush(stdout);
        size--;
    }
}

void  recursion(char *str)
{
    if(*str != '\0')
    {
        recursion(str +1);

    putchar(*str);
    fflush(stdout);
    }

}
int main()
{
    char str[]="india";
    char size=sizeof(str)/sizeof(str[0]) -1;

    printf("before reverse:%s \n",str);//sendif call by refrence , original is modifiying
    //reverse_string(str, size);
    //printf("aft reverse:%s \n",str);


   // reverse_string1(str, size);///for this below printf not required

   recursion(str);
   
    return 0;
}