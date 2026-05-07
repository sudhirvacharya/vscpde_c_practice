#include <stdio.h>


//fucntion inside structure
typedef struct {
    int x;
    int y;
    int (*add)(int a, int b);
} Calc;

int do_add(int a, int b)
 { 
 return a + b; 
 }
 
 
int main(void) {

    /* 1 */
    Calc c = { .x = 3, .y = 4, .add = do_add };
    printf("add = %d\n", c.add(c.x, c.y));      /* add = 7 */
	
	}
