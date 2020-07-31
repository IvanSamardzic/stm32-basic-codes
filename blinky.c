//PD12, PD13, PD14, PD15
//APB1
//RCC -> AHB1ENR 
//GPIODEN (bit3) in AHB1ENR
//GPIOD MODER, GPIOD ODR

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
		GPIOD->ODR |= 0x1000; 
		delayMs(1000);
		GPIOD->ODR &= 0xEFFF;
		delayMs(1000);
	}
}

void delayMs(int delay){
	int i;
	for(; delay>0 ; delay--){
		for(i=0; i<3195; i++){}
	}
}

