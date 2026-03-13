#include <stdio.h>
#include <stdlib.h>
void sort(int *array, int n)
{
    for(int i=0; i<n;i++)
    {
        for(int j=i+1;j<n; j++)
        {
            if(array[i] > array[j])
            {
                int tmp=array[i];
                array[i]=array[j];
                array[j]=tmp;
            }
        }
    }
}
int main()
{
    int array[]={2,1,7,4};
    int n=sizeof(array)/sizeof(array[0]);
    sort(array, n);
    for(int i =0 ; i<n; i++)
    {
        printf("sort %d \n", array[i]);
    }
    return 0;
}