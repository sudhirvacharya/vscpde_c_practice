#include <stdio.h>
#include <stdlib.h>

void reversebit(unsigned int n)
{ 
    unsigned int tmp=0;
    for(int i=0 ;i<32 ;i++)
    {
        tmp= (tmp <<1);
        tmp |= (n>>i) & 1;
       
        
    }
    printf("result: %x \n",tmp);
}
int main()
{
    unsigned int n=3;//0011
    reversebit(n);

    return 0;

}