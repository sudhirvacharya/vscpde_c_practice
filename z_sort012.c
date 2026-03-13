#include<stdio.h>
#include<stdlib.h>
//001212
//low-->0, mid-->1, high-->2


//input:0, 1, 2, 0, 1, 2
//output:0 0 1 1 2 2

void sort012(int *array, int n)
{
    int low=0, mid=0, high=n-1, tmp=0;
    while(mid <= high)
    {
        if(array[mid]==0)
        {
            tmp=array[mid];
            array[mid]=array[low];
            array[low] = tmp;
            low++;
            mid++;

        }
        else if (array[mid]==1)
        {
            mid++;
        }
        else //(array[mid]==2)
        {
            tmp=array[high];
            array[high]=array[mid];
            array[mid]=tmp;
            high--;
        
        }

    }
}
int main()
{
   int array[] = {0, 1, 2, 0, 1, 2};
   int n = sizeof(array)/sizeof(array[0]);
   sort012(array, n);
   for(int i=0; i<n ; i++)
        printf("sort012 %d \n", array[i] );

   return 0;
}