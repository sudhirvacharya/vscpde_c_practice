#include <stdio.h>

#if 1
int main()
{
/****************************************************************/
	/* When an int and an unsigned int of the same rank (width) are compared,
	 * the signed int is converted to unsigned due to the usual arithmetic conversions.
	 * x = 5 → 0x00000005
	 * y = -1 → 0xFFFFFFFF (two's complement, interpreted as unsigned = 4294967295)
	 * So the comparison becomes if (5 > 4294967295), which is false,
	 * and the program prints "test".
	 */

	unsigned int x=5;
	         int y=-1;
	if(x > y)
		printf("Sudheer \n");
	else
		printf("test\n");

    return 0;
}
#endif
#if 0
int main()
{
/**********************************************************************/
	/* In C, when an unsigned short and an int are compared,
	 * the usual arithmetic conversions apply. Since int has
	 * higher rank than unsigned short, x (unsigned short = 5)
	 * is promoted to int before comparison.
	 * So the comparison is (5 > -1), which is true,
	 * and the program prints "Sudheer".
	 */
	unsigned short x=5;
	         int y=-1;
	if(x > y)
		printf("Sudheer\n");
	else
		printf("test\n");

return 0;
   }
#endif

#if 0
int main() {
    int x = 3, y = 2;

    if (x-- > 3)
        printf("Hello\n");
    else
        printf("Bye\n"); //bye wiil print

    return 0;
}
#endif