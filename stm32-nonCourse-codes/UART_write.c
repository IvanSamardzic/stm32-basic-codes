#include "stm32f4xx.h"                  // Device header

//Forward method declarations
void USART2_init(void);
void USART2_write(int ch);
void delay_ms(int ch);

int main(void){
	//Initialise USART2 module
	USART2_init();
	//Do it forever
	while(1){
		USART2_write('H');
		USART2_write('e');
		USART2_write('l');
	 USART2_write('l');
		USART2_write('o');
		delay_ms(1000);
		USART2_write('\n');
	}
}
void USART2_init(void){
	//Enable clock access to USART2 module
	RCC->APB1ENR |= 0x20000;
	//Enable clock access to GPIOA module
	RCC->AHB1ENR |= 0x1;
	//Declare GPIOA as USART2 function 
	GPIOA->AFR[0] = 0x0700;
	//Declare PA2 as alternate function mode pin
	GPIOA->MODER |= 0x0020;
	//Configure USART2 registers, 0x0683->9600 bps at 16MHz
	USART2->BRR = 0x0683;
	//Enable USART2 transmitter
	USART2->CR1 = 0x0008;
	//Enable USART2 module
	USART2->CR1 |= 0x2000;
}

void USART2_write(int ch){
	//Wait while USART2 buffer is not full
	while(!(USART2->SR & 0x0080)){}
	//Load the character in the USART buffer
	USART2->DR = (ch & 0xFF);
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
