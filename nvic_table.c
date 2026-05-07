/* Vector table — array of function pointers
 * Placed at address 0x00000000 by linker script */
__attribute__((section(".vectors")))
const IRQ_Handler_t vector_table[] =
{
    (IRQ_Handler_t)&_stack_top,   /* 0: Initial Stack Pointer (not a function) */
    Reset_Handler,                /* 1: Reset                                  */
    /* External / Peripheral Interrupts (MCU specific) */
    ADC_Handler,                  /* 2: ADC global interrupt  <── ADC fires   */
    UART1_Handler,                /* 3: UART 1                                */
};

/* ADC Interrupt Handler — this IS the callback
 * CPU jumps here automatically when ADC conversion completes */
void ADC_Handler(void)
{
    /* Clear the interrupt flag first (always!) */
    ADC1->SR &= ~ADC_SR_EOC;

    /* Read result */
    adc_result = ADC1->DR;

    /* Notify application layer */
    Adc_GroupConversionComplete_Callback();
}
