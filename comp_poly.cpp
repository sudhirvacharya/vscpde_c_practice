#include <stdio.h>

//compile and run cmd
//g++ comp_poly.cpp 

//compile time polymorphism
//fucntion over lload also called polymorphism
//same name diffrent behavoir at compile time

// this is called fucnton over loading
void add( int a, int b)
{

printf( "int:->%d \n", a+b);
}

void add (float a, float b)
{
printf( "float:->%f \n", a+b);

}

int main()
{

add(2, 3);
add(4.3f, 4.3f);

return 0;
}