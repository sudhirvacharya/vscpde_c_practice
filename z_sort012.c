#include <stdio.h>
#include <stdlib.h>

void sort012(int *ptr, int n)
{
    /* Three pointers dividing array into zones:
     * [0..start-1]  = all 0s (sorted)
     * [start..mid-1]= all 1s (sorted)
     * [mid..end]    = unknown (to be processed)
     * [end+1..n-1]  = all 2s (sorted)
     */
    int start = 0, mid = 0, end = n - 1;
    int tmp;

    while (mid <= end)   /* keep going until unknown zone is empty */
    {
        if (ptr[mid] == 0)
        {
            /* 0 belongs in left zone: swap with start, expand both 0-zone and 1-zone */
            tmp = ptr[start];
            ptr[start] = ptr[mid];
            ptr[mid] = tmp;
            mid++;    //i had doubt why it here, this mid will transverse and pass to value to satar
            start++;    /* 0-zone grew by one */
        }
        else if (ptr[mid] == 1)
        {
            /* 1 is already in the correct middle zone, just move scanner forward */
            mid++;
        }
        else
        {
            /* 2 belongs in right zone: swap with end, shrink unknown zone from right */
            tmp = ptr[mid];
            ptr[mid] = ptr[end];
            ptr[end] = tmp;
            end--;      /* 2-zone grew by one */
            /* NOTE: mid does NOT move here — the swapped-in element is unexamined */
        }
    }
}

int main()
{
    int array[] = {2, 0, 1, 2, 0, 1, 0};
    int n = sizeof(array) / sizeof(array[0]);

    sort012(array, n);

    for (int i = 0; i < n; i++)
    {
        printf("sorted array: %d \n", array[i]);
    }
    return 0;
}