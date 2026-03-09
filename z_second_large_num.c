#include <stdio.h>
#include <stdlib.h>

//find secodn largest using sort and find second higest
void sort(int *ptr, int len)
{
    for(int j=0; j<len; j++)
    {
        for( int i=j+1; i<len; i++)
        {
            if(ptr[j] > ptr[i])
            {
                int tmp= ptr[j];
                ptr[j]=ptr[i];
                ptr[i]=tmp;
    
            }
        }
    } 

}

int main()
{
    int array[]={7, 4, 6, 2};
    int second_large;
    int len= sizeof(array)/sizeof(array[0]);
    printf("len %d\n ", len);
    sort(array, len);
    for(int i=0; i<len; i++)
    {
      printf("sort %d \n", array[i]);
    }
    second_large=array[len-2];
    printf("second_large %d \n", second_large);

    return 0;
}