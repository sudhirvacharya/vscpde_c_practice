#include <stdio.h>
//compile time polymorphism
//fucntion over lload also called polymorphism
//same name diffrent behavoir at compile time

// this is called fucnton over loading
void print( int a)
{

printf( "%d \n",a);
}

void print (float a)
{
printf( "%f \n",a);

}

int main()
{

print(2);
print(4.3f);

return 0;
}