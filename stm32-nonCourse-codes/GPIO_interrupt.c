#include "stm32f4xx.h"                  // Device header

void EXTI15_10_IRQHandler(void);
void delay_ms(int ch);

//Configuration: LED -> PA5, BUTTON -> PC13
int main(void){
	//Diasble the interrupt
		__disable_irq();
		//Enable clock access to GPIOA and GPIOC module
	RCC->AHB1ENR |= 1;
	RCC->AHB1ENR |= 4;
//Enable clock access to SYSCFG module
	RCC->AHB2ENR |= 0x4000;
	//Define PA5 pin as output 
	GPIOA->MODER |= 0x400; //0b 0100 0000 0000
	//Select GPIOC foe EXTI13
	SYSCFG->EXTICR[3] = 0x0020; 
	//Unmask EXTI13
	EXTI->IMR |= 0x2000;
	//Select interrupt on falling edge
	EXTI->FTSR |= 0x2000;
	//Enable interrupt
	NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void EXTI15_10_IRQHandler(void){
	GPIOA->BSRR = 0x20;
	delay_ms(300);
	GPIOA->BSRR = 0x0020;
	delay_ms(300);
}

void delay_ms(int ch){
	//Define SysTick registers
	SysTick->LOAD = 16000 - 1;
	SysTick->VAL = 0;
	SysTick->CTRL = 0x5;
	//For every milisecond wait while flag is not set
	for(int i = 0; i < ch; i++){
		while((SysTick->CTRL & 0x10000) == 0){}
	}
}
