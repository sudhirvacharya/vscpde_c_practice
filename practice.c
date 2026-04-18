#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
void printbin(uint8_t n)
{
    for(int i =7; i >=0 ; i--)
    {
        printf("%d", ((n>>i)&1) ? 1:0);
    }

}
void reversearray(int *array, int n)
{
    int left=0;
    int right=n-1;
    while(left <=right)
    {
        int tmp;
        tmp=array[left];
        array[left]=array[right];
        array[right]=tmp;
        left++;
        right--;

    }

}
uint8_t reversebin(uint8_t n)
{
    uint8_t tmp=0;
    for(int i=0; i<8 ;i++)
    {
        tmp=tmp<<1;
        tmp |= (n >>i) &1;
  
    }
    return tmp;
}
void revstring_rec(char *s)
{

    if(*s =='\0')
    {
        return;
    }

    revstring_rec(s+1);
    putchar(*s);
    fflush(stdout);

}
void ascending_order(int *a, int n)
{
    for(int i=0; i<n ;i++)
    {
        for(int j=i+1; j<n ;j++)
        {
            int tmp=0;
            if(a[i] > a[j])
            {
                tmp= a[i];
                a[i]=a[j];
                a[j]=tmp;
            }
        }
    }
}
void movezerotoend(int *a, int n)
{
    int left=0;
    int right=0;
    while(right < n)
    {
        if(a[right] != 0)
        {
            int tmp;
            tmp=a[right];
            a[right]=a[left];
            a[left]=tmp;
            left++;
        }
        right++;
    }
}
int removeduplicate(int *a, int n)
{
    for(int i=0; i<n ; i++)
    {
        for(int j=i+1; j <n; j++)
        {
            if(a[i]==a[j])
            {
                a[j]=a[n-1];
                n--;
                j--;
            }
        }
    }
    return n;
}
//{1,1,0};
void sort01(int *a, int n)
{
    int left=0;
    int right=0;
    int tmp;
    while(right < n)
    {
        if(a[left] !=0)
        {
            tmp=a[left];
            a[left]=a[right];
            a[right]=tmp;
            right++;
  
        }
        else
        {
            left++;
        }

    }
}

//int a[]={2,0,1,1,0,1,1,1,1};
void sort012(int a[], int n)
{
    int start=0;
    int mid=0;
    int end=n-1;
while(mid < end)
{
    int tmp;
    if(a[mid] ==0)//0
    {
        tmp=a[mid];
        a[mid]=a[start];
        a[start]=tmp;
        start++;
        mid++;

    }else if(a[mid]==1)//1
    {
        mid++;

    }
    else //2
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
     int a[]={0,0,2,1};
    int n=sizeof(a)/sizeof(a[0]);

sort012(a, n);

    for(int i=0; i<n; i++)
   {
    printf("%d",a[i]);

   }
  return 0;
}
