#include <stdio.h>
#include <stdlib.h>
void reverse_recursion(int *ptr, int left, int right)
{
  
    if(left >= right)
        return;

    int tmp;
    tmp=ptr[left];
    ptr[left]=ptr[right];
    ptr[right]=tmp;

   reverse_recursion(ptr, left +1, right -1);
   
 


}
int main()
{

    int array[]={2, 0,1, 5,6};
    int n=sizeof(array)/sizeof(array[0]);

    reverse_recursion(array, 0, n-1);
    for ( int i=0 ; i<n ; i++)
        printf("%d", array[i]);
    
    return 0;
}
