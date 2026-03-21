#include <stdio.h>
#include <stdlib.h>

int main()
{
    int array[]={2,2,3,3,4,4,4,1,1};
    int n =sizeof(array)/sizeof(array[0]);
    int odd_occ=0;
    for( int i =0 ; i<n ; i++)
         odd_occ ^= array[i];
    printf("odd ocurence %d \n", odd_occ);



    return 0;
}
