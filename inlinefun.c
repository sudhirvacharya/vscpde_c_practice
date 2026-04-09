#include <stdio.h>
#include <stdlib.h>

// Benefits: Reduces function call overhead (no pushing arguments/return addresses to the stack).
// Drawbacks: Excessive inlining can cause "code bloat" (larger binary size) and may increase cache misses.

// If you comment out the inline function and use a normal function call,
// you can observe changes in RBP and RSP (stack frame setup).
// With a normal function, the compiler generates prologue/epilogue code (push/pop).
// With inline, there is no function call overhead — the code is expanded directly.

// In Visual Studio, you may not see a difference because the compiler optimizes differently.
// In Eclipse/GCC, you can see the difference at compile time by commenting/uncommenting the inline function.
// In assembly, without inline you will see push/pop instructions for the function call.
// With inline, those push/pop operations disappear since the function body is inserted directly.

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