#include <stdio.h>

void sort(char *array, int n)
{

    for(int i=0 ; i< n; i++)
    {
        for( int  j=i+1 ;j<n ; j++)
        {
            if(array[i] > array[j])
            {
                char tmp;
                tmp= array[i];
                array[i]=array[j];
                array[j]=tmp;

            }


        }
    }

}
int main()
{
    char str1[]="anagram";
	char str2[]="ramanag";
    int n = sizeof(str1)/sizeof(str1[0]);
    sort(str1 , n-1);
    sort(str2 , n-1);
    for(int i=0 ; i<n ; i++)
    {
         printf("%c",str1[i]);

    }
    printf("\n");
    for(int i=0 ; i<n ; i++)
    {
        printf("%c",str2[i]);
    }
    printf("\n");

  
   
    return 0;
}