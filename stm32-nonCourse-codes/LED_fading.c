#include "stm32f4xx.h"                  // Device header

//forward mathod declarations
void GPIOA_init(void);
void ADC_init(void);
int ADC_read(void);
void PWM_init(void);
void PWM_set(int range);

//global system variable declarations
int value = 0;

int main(void){
	//Initialise the GPIOA, ADC1 and TIM2 module
	GPIOA_init();
	ADC_init();
	PWM_init();
	//Do it forever
	while(1){
		//Read ADC value on pin PA1 and set PWM on PA5
		value = ADC_read();
		value *= 5; 
		PWM_set(value);
	}
}
void GPIOA_init(void){
	//Enable clock access to GPIOA 
	RCC->AHB1ENR |= 0x1;
	//Declare PA5 as alternate function mode pin for TIM2
	GPIOA->AFR[0] = 0x00100000;
	GPIOA->MODER |= 0x00000800;
}

void ADC_init(void){
	//Enable access to GPIOA module
	RCC->AHB1ENR |= 0x1;
	//Declare PA1 as analog input mode pin
	GPIOA->MODER |= 0xC;
	//Enable clock access to ADC1 module
	RCC->APB2ENR |= 0x100;
	//Disable ADC1
	ADC1->CR2 = 0;
	//Set the first sequence at ADC1 CH1
	ADC1->SQR3 |= 0x1;
	//Enable th ADC1 module
	ADC1->CR2 |= 0x1;
}

int ADC_read(void){
	//Start AD conversion
	ADC1->CR2 |= 0x40000000;
	//Wait while ADC buffer is not full
	while(!(ADC1->SR & 0x2)){}
	return ADC1->DR;
}

void PWM_init(void){
	//Enable clock access to TIM2
	RCC->APB1ENR |= 0x01;
	//Set prescalers to generate 60Hz signal
	TIM2->PSC = 10 - 1;
	TIM2->ARR = 26667 - 1;
	//Set TIM2 to PWM mode
	TIM2->CNT = 0;
	TIM2->CCMR1 |= 0x60;
}

void PWM_set(int range){
	//Enable TIM2 
	TIM2->CCER |= 1;
	//Declare PWM raneg
	TIM2->CCR1 = range - 1;
	//Counter Enable
	TIM2->CR1 = 1;
}
