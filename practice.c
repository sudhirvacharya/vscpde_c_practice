#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

//sort 01
void movezerotoend(int *a, int n)
{

    int left=0;
    int right=0;
    while(right < n)
    {

        if(a[right] !=0)
        {
            int tmp;
            tmp=a[right];
            a[right]=a[left];
            a[left]=tmp;
            left++;
            right++;

            
        }
        else
        {
            right++;
        }


    }

}
int main()
{
    int a[]={1,0,0,1,0};
    int n=sizeof(a)/sizeof(a[0]);
    movezerotoend(a, n);
    for(int i=0;i<n ; i++)
    {
        printf("%d", a[i]);
    }

    return 0;
}