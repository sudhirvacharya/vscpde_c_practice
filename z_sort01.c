#include <stdio.h>
#include <stdlib.h>

// here comparing first and last 
//so right is n-1
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

/*

Step 0:  |0  1  0  0  1|   L=0,R=4  arr[L]=0 → L++
          L-----------R

Step 1:   0|1  0  0  1|    L=1,R=4  arr[L]=1 → swap(1,4) R--
            L--------R

Step 2:   0|1  0  0  1|    swap 1↔1, no visible change, R--
            L-----R

Step 3:   0|1  0  0| 1     L=1,R=3  arr[L]=1 → swap(1,3) R--
            L-----R

Step 4:   0  0|0  1| 1     L=1,R=2  arr[L]=0 → L++
               L--R

Step 5:   0  0  0|1| 1     L=2,R=2  arr[L]=1 → swap(2,2) R--
                 LR

Step 6:   L > R  STOP

Result:  {0  0  0  1  1}  ✅

*/