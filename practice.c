#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//print binary

void sot012( int *a, int n)
{

int start=0;
int mid =0;
int end=n-1;
while(mid <end)
{
    int tmp;
    // int a[]={0,0,1};
    if(a[mid]==0)
    {
        tmp=a[start];
        a[start]=a[mid];
        a[mid]=tmp;
        
        start++;
        mid++;

    }else if (a[mid] ==1)
    {
        mid++;
    }
    else //mid ==2
    {
        tmp=a[mid];
        a[mid]=a[end];
        a[end]=tmp;
        end--;

    }
   

}

}

int main()
{

    int a[]={2,1,0};
    //char a[]="india";
    int n= sizeof(a)/sizeof(a[0]);
    sot012(a, n);

    for(int i=0 ; i < n ; i++)
    {
        printf("%d",a[i]);
    } 




    return 0;

}