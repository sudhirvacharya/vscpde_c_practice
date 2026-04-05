#include <stdio.h>
#include <stdlib.h>

//move all zero to end using two pointers
/*
 <-- CLEAN ZONE -->|<-- UNSORTED -->
  1   2   4   3   |  0   0   5   0
                  ^           ^
                  L           R
*/

//left of array always zero expect irt iteration
void moveZerotoEnd(int *arr, int n)
{
    int left=0;
    int right=0;
    while(right < n)
    {

        if(arr[right] != 0)
        {
            /* swap: non-zero at R goes to the clean-zone boundary L */
            int tmp = arr[right];
            arr[right] = arr[left];
            arr[left]=tmp;
            left++;
        }
        right++;
    }

}
int main()
{
    int arr[] = {1, 2, 0, 4, 3, 0, 5, 0};
    int n= sizeof(arr)/sizeof(arr[0]);
    moveZerotoEnd(arr, n);
    for(int i=0; i < n ; i++)
        printf("moveZerotoEnd %d\n", arr[i]);
    return 0;
}