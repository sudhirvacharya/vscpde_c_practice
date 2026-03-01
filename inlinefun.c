#include <stdio.h>
#include <stdlib.h>


//Benefits: Reduces overhead (pushing arguments/return addresses to the stack).
//Drawbacks: Excessive inlining can cause "code bloat" (larger binary size) and increase cache misses
	//observer rbp and rsp by commentiong inlin_add funtion
	//main stack fram will increase if we add fucntion
	//only thin is no fucntion over head push or pop
	//in asm also you can verigy there is no push pop operation


//in vs studio i am not seeing diffrence, but in eclispse ican see,
// you can see it in compile time only.by commneting and adding fcuntion
// in asmu can see without inline there is push pop ocde, with inline u can see with puh pop operation
inline int add(int a, int b) __attribute__((always_inline));


__attribute__((always_inline)) inline int add(int a, int b) {
    int c;
   return c=a+b;
 


}
int main()
{

    int a=10, b=20;
    printf("result %d \n", add(a,b));
    // printf("result %d \n", add(a,b));

    return 0;
}