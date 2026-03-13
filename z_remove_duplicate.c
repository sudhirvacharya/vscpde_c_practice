#include<stdio.h>
#include<stdlib.h>
int duplicate(int *array, int n)
{
    for(int i=0; i<n ;i++)
    {
        for(int j=i+1 ;j<n ;j++)
        {
            if(array[i]==array[j])
            {
                array[j]=array[n-1];
                n--;
                j--;
            }
        }
    }
    return n;
}
int main()
{
    int array[]={1,2,3,2,1,10,5};
    int n=sizeof(array)/sizeof(array[0]);
    n=duplicate(array, n);
    for(int i=0; i<n ;i++)
     printf("array %d \n",array[i]);
}
