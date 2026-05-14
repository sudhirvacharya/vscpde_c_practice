#include <stdio.h>
#include <stdlib.h>

void Adc_Init()
{

	RCC->CFGR |= (6 <<12); //APB = HCLK/8 = 8Mhz
	RCC->APBENR2 |= (1<<20); //adc clock
	if(ADC1->ISR & (1<<0)) //ADC READY
	{
		ADC1->CR |= 1<<1;//DISABLED ADC
	}
	ADC1->CR |= 1<<28; //REGULATOR ENABLE
	delay_ms(1);
	ADC1->CR |= 1<<31; //ADC CALIBARATION STARTED
	delay_ms(1);
	while(ADC1->CR & (1<<31));


}
void Adc_Cfg(uint8_t ch)
{
	//22,24
	ADC1_COMMON->CCR |= (1<<24); //VBAT

	ADC1_COMMON->CCR |= (1<<22); //VREGU
	delay_ms(10);
	ADC1->CHSELR |= (1<<ch);
	ADC1->SMPR |= 4<<0; //SAMPLING RATE
	ADC1->CR |= 1<<0; //ADC EN
	while(!(ADC1->ISR & (1<<0))); //AD   RDY
}

uint16_t Adc_Read()
{
	ADC1->CR |= 1<<2; //ADC START
	while(!(ADC1->ISR & (1<<2))); //eoc
	return ADC1->DR;

}

#define DEBUG 1
int main(void)
{
	uint16_t raw_value;

	float voltage;
	Adc_Init();
	while(1)
	{
		Adc_Cfg(14); //p7

		raw_value=Adc_Read();
		raw_value1= raw_value;
		voltage = (raw_value*3.3)/4095 ;
	}


}