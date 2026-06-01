#include <stdio.h>
//					(**ptr)          (*ptr)
//adress of ptr-->0x7ffdb66bda60-->   nill   
//adress of ptr-->0x7ffdb66bda60-->   0x580cb5e2a010   -->100
//adress of ptr-->0x7ffdb66bda60-->   0x580cb5e2a014   -->200


int a = 100; // stored at some address, let's call it 0x5dc5759fa010
int b = 200; // stored at some address, let's call it 0x2000



void fna(int **pp)
{
    // pp  = address of ptr  (e.g. 0x4000)  -- the double pointer itself
    // *pp = value inside ptr               -- which address ptr is pointing to
    // **pp= value at that address          -- the actual int data

    printf("\n--- inside fna() ---\n");
    printf(" pp        (addr of ptr)    --> %p\n",  pp);   // 0x4000
    printf(" *pp       (ptr value)      --> %p\n",  *pp);  // NULL before assignment
    // NOTE: **pp here would segfault because *pp is still NULL -- so we assign first
    *pp = &a;                                               // make ptr point to a
	printf(" a adress   --> %p\n",  &a);  // 0x1000
    printf(" *pp       (ptr now -> a)   --> %p\n",  *pp);  // 0x1000
    printf(" **pp      (value at a)     --> %d\n", **pp);  // 100
}

void fnb(int **pp)
{
    printf("\n--- inside fnb() ---\n");
    printf(" pp        (addr of ptr)    --> %p\n",  pp);   // still 0x4000
    printf(" *pp       (ptr value)      --> %p\n",  *pp);  // currently 0x1000 (a)
    *pp = &b;    
	printf(" b adress-->       --> %p\n",  &b);  // 0x2000                                           // redirect ptr to b
    printf(" *pp       (ptr now -> b)   --> %p\n",  *pp);  // 0x2000
    printf(" **pp      (value at b)     --> %d\n", **pp);  // 200
}

int main()
{
    int *ptr = NULL;

    printf("=== initial state ===\n");
    printf(" &ptr      (addr of ptr)    --> %p\n",  &ptr); // 0x7ffe654e0840
    printf(" ptr       (ptr value)      --> %p\n",  ptr);  // NULL
    // *ptr here would segfault -- ptr points nowhere yet

    fna(&ptr);

    printf("\n=== after fna() ===\n");
    printf(" &a        (addr of a)      --> %p\n",  &a);   // 0x1000
    printf(" ptr       (ptr value)      --> %p\n",  ptr);  // should equal &a
    printf(" *ptr      (value at ptr)   --> %d\n", *ptr);  // 100
	 printf(" &ptr      (addr of ptr)    --> %p\n",  &ptr);

    fnb(&ptr);

    printf("\n=== after fnb() ===\n");
    printf(" &b        (addr of b)      --> %p\n",  &b);   // 0x2000
    printf(" ptr       (ptr value)      --> %p\n",  ptr);  // should equal &b
    printf(" *ptr      (value at ptr)   --> %d\n", *ptr);  // 200
	 printf(" &ptr      (addr of ptr)    --> %p\n",  &ptr);

    return 0;
}