#include "stm32f4xx.h"                  // Device header
void USART2_init(void);
int USART2_read(void);
void GPIOA_init(void);
void PA5_play(int delay);
void delay_ms(int ch);

int readValue = 0;

int main(void){
	USART2_init();
	GPIOA_init();
	while(1){
		readValue = USART2_read();
		PA5_play(readValue);
	}
}
void USART2_init(void){
	//Enable clock access to USART2 module
	RCC->APB1ENR |= 0x20000;
	//Enable clock access to GPIOA module
	RCC->AHB1ENR |= 0x1;
	//Declare GPIOA as USART2 function 
	GPIOA->AFR[0] = 0x7000;
	//Declare PA3 as alternate function mode pin
	GPIOA->MODER |= 0x0080;
	//Configure USART2 registers, 0x008B -> 115200 bps at 16MHz
	USART2->BRR = 0x008B;
	//Enable USART2 transmitter
	USART2->CR1 = 0x0004;
	//Enable USART2 module
	USART2->CR1 |= 0x2000;
}

int USART2_read(void){
	//Wait while the haracter come
	while(!(USART2->SR & 0x0020)){}
	return USART2->DR;
}

void GPIOA_init(void){
	//Enable clock access to GPIOA
	RCC->AHB1ENR |= 0x1;
	//Set PA5 as output mode pin
	GPIOA->MODER |= 0x400;
}

void PA5_play(int delay){
	//Toggle the PA5 state
	GPIOA->ODR ^= 0x20;
	delay_ms(delay);
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
