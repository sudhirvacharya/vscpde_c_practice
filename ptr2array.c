#include <stdio.h>

int main()
{
    int a[]={2,3,5,6};
    int (*ptr)[]=&a;
    int n=sizeof(a)/sizeof(a[0]);
    
    for( int  i=0; i<n ;i++)
    {
        printf("%d",(*ptr)[i]);
    }


    return 0;
}