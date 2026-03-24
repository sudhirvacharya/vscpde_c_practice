#include <stdio.h>
#include <stdlib.h>
/*  this works only for odd number of repeation 1,3,5,7,9...

00->0
01->1
10->0
11->0

//if the odd input, output willl be high
000->0
001->1
010->1
011->0

*/
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
