#include <stdio.h>
#include <stdlib.h>
void reverse_str(char *ptr, int n)
{
    while(n)
    {
        putchar(ptr[n-1]);
        fflush(stdout);
        n--;
    }

}
void recur_reverse_str(char *ptr)
{
    if(*ptr != '\0')
    {
        recur_reverse_str(ptr +1);
         putchar(*ptr);
         fflush(stdout);

    }
   
}

void reverse12(char *ptr, int n)
{
    int left =0;
    int right=n-1;
    char tmp;

    while(left < right)
    {
        tmp= ptr[left];
        ptr[left]=ptr[right];
        ptr[right]=tmp;
        left++;
        right;;
    }
}
int main()
{
    char str[]="india";
    int n=sizeof(str)/sizeof(str[0]);
    //reverse_str(str, n-1);
    //recur_reverse_str(str);

    reverse12(str, n-1);
    printf("%s",str);

       
    return 0;
}