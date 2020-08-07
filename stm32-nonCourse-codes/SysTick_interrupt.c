#include "stm32f4xx.h"                  // Device header
void SysTick_Handler(void);

int main(void){
	//Disable interrupt
	__disable_irq();
	//Enable clock access to GPIOA module
	RCC->AHB1ENR |= 0x1;
	//Declare PA5 as output mode pin
	GPIOA->MODER |= 0x400;
	//Configure SysTick Timer, 1 Hz interrupt signal
	SysTick->LOAD = 16000000 - 1;
	SysTick->VAL = 0;
	SysTick->CTRL = 7;
	//Enable interrupt
	__enable_irq();
	while(1){}
}

void SysTick_Handler(void){
	//Toggle PA5 pin state at every interrupt
	GPIOA->BSRR ^= 0x20;
}
