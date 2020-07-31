#include "stm32f4xx.h"                  // Device header
void delayMs(int delay);

int main(void){
	// Enable the clock access to GPIOD
	RCC->AHB1ENR |= 0x8;
	// Set PD12, PD13, PD14, PD15 as output pins
	// 0x55000000 -> 0b 0101 0101 0000 0000 0000 0000 0000 0000
	GPIOD->MODER |= 0x55000000;
	while(1){
		// Turn on the LED connected to PD12
		GPIOD->BSRR |= 0x1000; 
		// Wait for 1000ms
		delayMs(1000);
		// Turn off the LED
		GPIOD->BSRR |= 0x10000000;
		// Wait for 1000ms
		delayMs(1000);
	}
}

void delayMs(int delay){
	int i;
	for(; delay>0 ; delay--){
		for(i=0; i<3195; i++){}
	}
}


