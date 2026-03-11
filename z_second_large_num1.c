#include <stdio.h>
#include <stdlib.h>

//find secodn largest using sort and find second higest
void sort(int *ptr, int len)
{
    int first_higest, second_higest;
    first_higest=ptr[0];
    for(int i=0; i<len; i++)
    {
        if(ptr[i]>first_higest)
            first_higest=ptr[i];
    }
    second_higest=ptr[0];
    for(int i=0; i<len; i++)
    {
        if(ptr[i]<first_higest && ptr[i]>second_higest)
            second_higest=ptr[i];
    }
    printf("first_higest %d\n, second_higest%d\n ",first_higest, second_higest);


}

int main()
{
    int array[]={7, 4, 6, 2};

    int len= sizeof(array)/sizeof(array[0]);
    printf("len %d\n ", len);
    sort(array, len);


    return 0;
}