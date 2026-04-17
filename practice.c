#include <stdio.h>
#include <stdint.h>
//anagram

void  checkanagram(char *str1,char * str2, int n)
{
    char alpha[25];
    char result1[25];
    char result2[25];
    for(int i=0 ; i <n ; i++)
    {
        alpha[i]='0'+i;

    }
    for(int i=0 ; i< n; i++)
    {
        if(str1[i]==alpha[i])
        {

        }

    }

}
int main()
{
    char str1[]='anagram';
    char str2[]='mnagraa';
    int n1 =sizeof(str1)/sizeof(str1[0]);
    int n2 =sizeof(str2)/sizeof(str2[0]);

    if( n1 != n2)
    {
        printf("not a anagram");

    }
    checkanagram(str1, str2, n1-1);


    



    return 0;
}
