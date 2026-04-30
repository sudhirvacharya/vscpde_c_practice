#include <stdint.h>
#include "stm32g070xx.h"

// Simple delay loop
void delay(){
// Loop 300000 times to create delay
    for(int i=0;i<300000;i++);
}

// UART receive buffer
uint8_t rx_buff[256];

// Set GPIO pin mode
// port=A/B/C, pin=0-15
// mode: 0=Input 1=Output
// 2=AltFunc 3=Analog
void set_GPIO_mode(char port, uint8_t pin, uint8_t mode)
{
    switch (port)
    {
        case 'A':
            // Enable GPIOA clock
            #ifdef STM32F072xB
                RCC->AHBENR |= (1<<17);
            #elif defined STM32G071xx
                RCC->IOPENR |= (1<<0);
            #elif defined STM32G070xx
                RCC->IOPENR |= (1<<0);
            #endif
            // Clear pin mode bits
            GPIOA->MODER &= ~(3 << (pin*2));
            // Set new mode
            GPIOA->MODER |= (mode << (pin*2));
            break;

        case 'B':
            // Enable GPIOB clock
            #ifdef STM32F072xB
                RCC->AHBENR |= (1<<18);
            #elif defined STM32G071xx
                RCC->IOPENR |= (1<<0);
            #elif defined STM32G070xx
                RCC->IOPENR |= (1<<1);
            #endif
            // Clear pin mode bits
            GPIOB->MODER &= ~(3 << (pin*2));
            // Set new mode
            GPIOB->MODER |= (mode << (pin*2));
            break;

        case 'C':
            // Enable GPIOC clock
            #ifdef STM32F072xB
                RCC->AHBENR |= (1<<19);
            #elif defined STM32G071xx
                RCC->IOPENR |= (1<<0);
            #elif defined STM32G070xx
                RCC->IOPENR |= (1<<2);
            #endif
            // Clear pin mode bits
            GPIOC->MODER &= ~(3 << (pin*2));
            // Set new mode
            GPIOC->MODER |= (mode << (pin*2));
            break;

        default:
            break;
    }
}

// Init USART2
// TX=PA2 RX=PA3
// Baud=9600 @16MHz
void uart2_init(){
    // Enable USART2 clock
    RCC->APBENR1 |= (1<<17);

    // PA2 = AltFunc (TX)
    set_GPIO_mode('A', 2, 2);
    // Set AF1 on PA2
    GPIOA->AFR[0] |= (1<<8);

    // PA3 = AltFunc (RX)
    set_GPIO_mode('A', 3, 2);
    // Set AF1 on PA3
    GPIOA->AFR[0] |= (1<<12);

    // Set baud rate 9600
    USART2->BRR = 0x682;
    // Enable RX interrupt
    USART2->CR1 |= (1<<5);
    // Enable USART2 in NVIC
    NVIC->ISER[0] |= (1<<28);
    // Enable Transmitter
    USART2->CR1 |= (1<<3);
    // Enable Receiver
    USART2->CR1 |= (1<<2);
    // Enable USART2
    USART2->CR1 |= (1<<0);
}

// Blocking read one char
int get_char(){
    // Wait until RX ready
    while(!(USART2->ISR & (1<<5)));
    // Return received byte
    return USART2->RDR;
}

// Blocking send one char
void put_char(char ch){
    // Wait until TX empty
    while(!(USART2->ISR & (1<<7)));
    // Send the character
    USART2->TDR = ch;
}

// USART2 RX interrupt
void USART2_IRQHandler(){
    // Store received byte
    // clears RXNE flag
    rx_buff[0] = USART2->RDR;
}

// Send string over UART
void send_str(char *ptr){
    // Loop until null char
    while(*ptr){
        // Send each character
        put_char(*ptr++);
    }
}

int main(void)
{
    // Store received char
    char ch;

    // Init USART2
    uart2_init();
    // Send hello string
    send_str("hello");
    // Wait for 1 char RX
    ch = get_char();

    // Enable GPIOA clock
    RCC->IOPENR |= (1<<0);

    // Clear PA5 mode bits
    GPIOA->MODER &= ~(0xC00);
    // Set PA5 as output
    GPIOA->MODER |= (0x400);

    // Blink LED forever
    for(;;){
        // PA5 HIGH - LED ON
        GPIOA->BSRR |= (1<<5);
        delay();
        // PA5 LOW - LED OFF
        GPIOA->BSRR |= (1<<21);
        delay();
    }
}
`
 