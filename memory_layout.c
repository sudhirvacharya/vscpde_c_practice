#include <stdio.h>
#include <stdlib.h>

int main()
{

    	int a = 0x02;          // an integer
	    int *ptr = &a;         // pointer to int
	    int **ptr_ptr = &ptr;  // pointer to pointer to int

        int a_stack;
    static int b_bss;
    static int c_init=8;
    volatile register int d_reg=10;
  //  char *ptr="ro_data";
    char *buff_ptr=malloc(10);

    printf("a_stack adress=%p \t",&a_stack);
    printf("a_stack data=%d\n",a_stack);

    printf("b_bss adress=%p\t",&b_bss);
    printf("b_bss data =%d\n",b_bss);

    printf("c_init adress=%p \t",&c_init);
     printf("c_init data=%d \n",c_init);

    //printf("d_reg adress=%p \t",&d_reg);/* this will not due ti register will not give acess to user*/
       printf("d_reg data=%d \n",d_reg);

       printf("ptr adress=%p \t",&ptr);
           printf("ptr data=%#lx \n",ptr);

           printf("buff_ptr adress=%p \t",&buff_ptr);
                   printf("buff_ptr data=%#lx \n",buff_ptr);

                   if (buff_ptr)
                	  free(buff_ptr) ;




	    printf("a: %d\n", a);
	    printf("*ptr: %d\n", *ptr);
	    printf("**ptr_ptr: %d\n", **ptr_ptr);

	    // Print addresses
	    printf("\nAddresses:\n");
	    printf("&a: %p\n", (void*)&a);
	    printf("ptr (address of a): %p\n", (void*)ptr);
	    printf("&ptr: %p\n", (void*)&ptr);
	    printf("ptr_ptr (address of ptr): %p\n", (void*)ptr_ptr);
	    printf("&ptr_ptr: %p\n", (void*)&ptr_ptr);

    return 0;
}

/*

High Address
+---------------------------+
|         STACK             |
|  0x7ffe0be28790  a_stack  |  local var, value=0 (uninitialized local)
|  0x7ffe0be28798  ptr      |  pointer variable lives on stack
|  0x7ffe0be287a0  buff_ptr |  pointer variable lives on stack
+---------------------------+
|                           |
|      (free space)         |
|                           |
+---------------------------+
|         HEAP              |
|  0x618afd6392a0  ◄──────────── buff_ptr points here (large gap!)
|                           |
|  0x618adea26004  ◄──────────── ptr points here
+---------------------------+
|         .BSS              |
|  0x618adea28018  b_bss    |  value=0, uninitialized global
+---------------------------+
|         .data             |
|  0x618adea28010  c_init   |  value=8, initialized global
+---------------------------+
|         .text / .rodata   |
+---------------------------+
Low Address
*/
