int *ptr= NULL;
----------------------
addr   data   expression 
0x100   NULL  ptr
			||
			||(if we pass to double pointer)
			||
            \/
int **ptr;
ptr  = malloc(sizeof(int*));  // allocates 0x200, stores in 0x100
*ptr = malloc(sizeof(int));   // allocates 0x300, stores in 0x200
**ptr = 42;                   // writes 42 into 0x300
----------------------
adress   data      ptr
0x100     0x200     ptr
0x200    0x300     *ptr
0x300    42       **ptr