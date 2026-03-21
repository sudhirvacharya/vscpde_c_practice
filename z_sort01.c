#include <stdio.h>
#include <stdlib.h>
void sort01(int *array, int n)
{
    int tmp=0;
    int left=0;
    int right=n-1;
    while(left <= right)
    {
        if(array[left] !=0)
        {
            tmp = array[left];
           array[left]= array[right];
           array[right]=tmp;
           right--;
        }
        else
        {
            left++;
        }
    }
}
int main()
{

    int array[]={1,0,1,1,1,0,0,1,0};
   int n=sizeof(array)/sizeof(array[0]);
    sort01(array, n);
    for( int i=0 ;i<n ; i++)
    printf( "%d",array[i]);

    return 0;


}