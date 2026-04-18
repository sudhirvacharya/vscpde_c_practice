#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define bit 8
bool bits;
void displaybits(unsigned char n)
{
    for(int i=7 ;i >=0 ;i--)
    {
        bits =( n >> i ) &1;

        printf(" %c ",     bits > 0 ?  '1' : '0'       ) ;
    }

}
//https://www.browserling.com/tools/rotate-binary-right
int main()
{
    unsigned char var=67;//rottat left 01000011, outpput  -->00011010
    unsigned char var1=67;//rottat right 01000011, outpput  -->01101000
    unsigned char r=3;//0000 0011

    printf("before rotate left\n");
    displaybits(var);
    //left shift operator
    var = (var << r) |( var >> (bit - r) );
    printf("aft rtae left\n");
    displaybits(var);

//rotate right operator
  printf("before rotate right\n");
    displaybits(var1);

    var1 = (var1 >> r ) | var1 << (bit -r);
      printf("aft rotate right\n");
    displaybits(var1);




}