#include "stm32f4xx.h"                  // Device header

//Forward method definitions
void USART2_init(void);
void delay_ms(int ch);
void LED_toggle(int value);
void USART2_IRQHandler(void);

int main(void){
	//Disable the global interrupt
	__disable_irq();
	//Enable clock access to GPIOA module
	RCC->AHB1ENR |= 0x1;
	//Declare PA5 as output mode pin
	GPIOA->MODER |= 0x400;
	//Initialise USART2 module
	USART2_init();
	//Enable RX interrupt 
	USART2->CR1 |= 0x0020;
	//Define Interrupt Routine (NVIC)
	NVIC_EnableIRQ(USART2_IRQn);
	//Enable global interrupt
	__enable_irq();
	
	//Do it forever
	while(1){}
}

void USART2_init(void){
	//Enable clock access to GPIOA module
	RCC->AHB1ENR |= 0x1;
	//Enable clock access to USART2 module
	RCC->APB1ENR |= 0x20000;
	//Set GPIOA pin as alternate function mode pin
	GPIOA->AFR[0] |= 0x7000;
	//Declare PA3 as alternate function mode pin
	GPIOA->MODER |= 0x0080;
 
	//Set USART2 configuration
	USART2->BRR = 0x008B; 
	USART2->CR1 = 0x0004;
	USART2->CR1 |= 0x2000;
}

void LED_toggle(int value){
	//Constraint the value variable to 16
	value %= 16;
	//Toggle the LED value times
	for(; value > 0; value--){
		GPIOA->BSRR = 0x20;
		delay_ms(500);
		GPIOA->BSRR = 0x0020;
		delay_ms(500);
	}
	delay_ms(500);
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

void USART2_IRQHandler(void){
	//Define c variable
	char c;
	//check if buffer is full
	if(USART2->SR & 0x0020){
		//Put data register into c variable
		c= USART2->DR;
		//Toggle the LED
		LED_toggle(c);
	}
}
