//TIM2 general purpose timer

#include "stm32f4xx.h"                  // Device header

int main(void){
	//Enable clock access to GPIOA and declare PA5 pin as output pin
	RCC->AHB1ENR |= 0x1;
	GPIOA->MODER |= 0x400;
	
	//Timer2 configuration
	//Enable clock access to TIM2
	RCC->APB1ENR |= 0x1;
	
	//Prescaler 1600
	TIM2->PSC = 1600 - 1;
	
	//Divide by 10000 to generate 1Hz timer signal
	TIM2->ARR = 10000 - 1;
	
	//Declare TIM2 counter register value
	TIM2->CNT = 0;
	
	//Enable TIM2
	TIM2->CR1 = 1;
	
	//Do it forever
	while(1){
		//wait while flag is not raised in status register
		if((TIM2->SR && 1)){
			//clear the flag and toggle the PA5 pin
			TIM2->SR &=!1;
			GPIOA->ODR ^=0x20;
		}
	}
}
