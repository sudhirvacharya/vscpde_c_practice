#include <stdio.h>
#include <stdlib.h>
//odd occcurance
int main()
{
    int array[]={2,3,3,4,3,4,2};
    int tmp=0;
    for( int i=0 ;i <7; i++)
    {
         tmp ^=array[i];
    }
    printf("%d \n", tmp);




    
    
    return 0;

}