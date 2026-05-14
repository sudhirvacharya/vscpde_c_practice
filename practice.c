#include <stdio.h>

typedef struct Char4 {
    char data[5];
} char4_t;

//Function that receives a char4_t and returns it encrypted according to specified instructions
char4_t encryptText(char4_t input) {
    char4_t  output; //Output will be input encrypted

    //For loop that processes each character of input individually
    for (int i = 0; i < sizeof(input.data)-1; i++) {
        int digit = input.data[i] - '0'; //Converting character to int to perform arithmetic operations
        printf("Digit %d before encryption: %d\n", i, digit);
        digit += 7;
        digit %= 10;
        printf("Digit %d after encryption: %d\n", i, digit);
        output.data[i] = (char) digit; //HERE WE HAVE A PROBLEM
        printf("output.data[%d]: %c\n", i, output.data[i]);
    } //for

    printf("\n");

    /*After arithmetic operations, instructions state to swap
    first character with fourth and second with third*/
    char buffer = output.data[0];
    output.data[0] = output.data[2];
    output.data[2] = buffer;
    buffer = output.data[1];
    output.data[1] = output.data[3];
    output.data[3] = buffer;

    return output;
} //encryptText

int main(void) {
    char4_t text;
    text.data[0]='0';
     text.data[1]='1';
      text.data[2]='2';
       text.data[3]='3';
  
    char4_t encrypted;

    printf("Introduce text to encrypt: ");
    //fgets(text.data, sizeof(text.data), stdin);

    encrypted = encryptText(text);
    return 1;
} //main
