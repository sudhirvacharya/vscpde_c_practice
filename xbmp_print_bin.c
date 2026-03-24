#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


bool bits;
void displaybits(unsigned char n)
{
    for(int i=7 ;i >=0 ;i--)
    {
        bits =( n >> i ) &1;

        printf(" %c ",     bits > 0 ?  '1' : '0'       ) ;
    }

}
int main()
{
    
    displaybits(6);



    return 0;
}