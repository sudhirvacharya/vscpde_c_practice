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

int main()
{
    char str[]="india";
    char size=sizeof(str)/sizeof(str[0]) -1;

    printf("before reverse:%s \n",str);//sendif call by refrence , original is modifiying
    reverse_string(str, size);
    printf("aft reverse:%s \n",str);
    return 0;
}