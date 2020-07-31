#include "stm32f4xx.h"                  // Device header

int main(void){
	uint16_t value = 0;
	//Enable clock access to GPIOA
	RCC->AHB1ENR |= 0x01;
	//Set PA5 pin as one for TIM2 altrnate function (PWM mode)
	GPIOA->AFR[0] |= 0x00100000;
	//Define PA5 as alternate function mode pin (0b10)
	GPIOA->MODER |= 0x00000800;
	
	//Timer Setup
	//Enable clock access to TIM2
	RCC->APB1ENR |= 0x01;
	//Set Prescaler to 10 Timer_freq = 16M / 100	= 0,16MHz
	TIM2->PSC = 10 - 1;
	//Additional prescaler is 26667 Timer_freq = 6Hz
	TIM2->ARR = 26667 - 1;
	//TIM2 counter is set to 0
	TIM2->CNT = 0;
	//Declare PWM mode
	TIM2->CCMR1 = 0x0060;
	//OC1 signal is declared as output
	TIM2->CCER = 1;
	//Capture compare register, PWM is counting up to this value
	TIM2->CCR1 = value - 1;
	//Enable the TIM2 module
	TIM2->CR1 = 1;
	
	while(1){
		for(int i = 1; i>0 ; i++){
			value += 500;
		}
	}
}
