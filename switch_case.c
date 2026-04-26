#include <stdio.h>
int main() {
   int day = 3;
   switch (day) {
       case 1:
           printf("Monday");
           break;
       case 2:
           printf("Tuesday");
           break;
       default:
           printf("Invalid day number");
   }
   return 0;
}