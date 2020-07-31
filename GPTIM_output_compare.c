#include "stm32f4xx.h"                  // Device header

//Toggling LED using TIM2 compare match mode declaring PA5 pin as
//alternate mode pin

int main(void){
	//Enable clock access to GPIOA and TIM2 modules
	RCC->AHB1ENR |= 0x1;
	RCC->APB1ENR |= 0x1;
	
	//Define PA5 as alternate function mode pin
	GPIOA->MODER |= 0x800;
	GPIOA->AFR[0] |= 0x00100000;
	
	//Define TIM2 registers
	//Define prescaler value as 1600, define ARR register as 1000 to generate 10Hz signal
	TIM2->PSC = 1600 - 1;
	TIM2->ARR = 1000 - 1;
	
	//Set output to toggle on compare match value
	TIM2->CCMR1 = 0x30; 
	
	//Set match mode
	TIM2->CCR1 = 0;
	
	//Enable CH1 on compare match
	TIM2->CCER |= 0x1;
	
	//Clear counter register
	TIM2->CNT = 0;
	
	//Enable TIM2 module
	TIM2->CR1 = 1;
	
	while(1){
	}
}
