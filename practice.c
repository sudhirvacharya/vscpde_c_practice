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
int main()
{  
    

    int array[]={2,3,3,1,1,1,1};
    uint8_t res=0;
    int n=sizeof(array)/sizeof(array[0]);

    printf("%d \n",res);
    

  
   //reversearray(array, n);
   
   res=reversebin(3);//0011
   printbin(res);
   /*
   for(int i=0; i<n; i++)
   {
    printf("%d",array[i]);

   }*/
    
    return 0;
}
