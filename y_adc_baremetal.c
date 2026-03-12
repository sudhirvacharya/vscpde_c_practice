#include "stm32g0xx.h"

void ADC_Init(void)
{
    /* 1. Enable clocks */
    RCC->IOPENR  |= RCC_IOPENR_GPIOAEN;
    RCC->APBENR2 |= RCC_APBENR2_ADC1EN;   // ← fixed macro

    /* 2. PA0 → analog, no pull */
    GPIOA->MODER &= ~(0x3U << 0);         // ← clear first
    GPIOA->MODER |=  (0x3U << 0);         // analog mode
    GPIOA->PUPDR &= ~(0x3U << 0);         // no pull

    /* 3. Enable voltage regulator */
    ADC1->CR |= ADC_CR_ADVREGEN;
    for (volatile int i = 0; i < 80000; i++); // ← volatile + longer delay

    /* 4. Calibrate BEFORE enabling */        // ← was missing entirely
    ADC1->CR |= ADC_CR_ADCAL;
    while (ADC1->CR & ADC_CR_ADCAL);

    /* 5. Set sampling time & channel */
    ADC1->SMPR  |= ADC_SMPR_SMP1_0 | ADC_SMPR_SMP1_1;
    ADC1->CHSELR = ADC_CHSELR_CHSEL0;     // = not |= (avoid stale bits)

    /* 6. Enable ADC */
    ADC1->ISR |= ADC_ISR_ADRDY;           // clear stale ADRDY
    ADC1->CR  |= ADC_CR_ADEN;
    while (!(ADC1->ISR & ADC_ISR_ADRDY));
}

uint16_t ADC_Read(void)
{
    ADC1->CR |= ADC_CR_ADSTART;
    while (!(ADC1->ISR & ADC_ISR_EOC));
    uint16_t val = (uint16_t)(ADC1->DR & 0x0FFF);  // ← mask 12-bit
    ADC1->ISR |= ADC_ISR_EOC;                       // ← explicit clear
    return val;
}

int main(void)
{
    ADC_Init();
    while (1)
    {
        uint16_t value = ADC_Read();
        (void)value;
    }
}