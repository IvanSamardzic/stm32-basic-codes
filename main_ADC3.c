//Reading potentiometer value
//using ADC1 module 

#include "stm32f4xx.h"                  // Device header
static unsigned int analogValue;

int main(void){
	// Enable clock access to GPIOA
	RCC->AHB1ENR |= 0x1;
	
	// Set PA1 as analog input pin
	GPIOA->MODER |= 0xC;
	
	// Enable clock access to ADC1 module
	RCC->APB2ENR |= 0x100;
	
	// Disable ADC1 module
	ADC1->CR2 |= 0x0;
	
	// Set start sequence 
	ADC1->SQR3 |= 0x1;
	
	// Enable ADC module
	ADC1->CR2 |= 0x1;
	
	// Do it forever
	while(1){
		// Start conversion 
		ADC1->CR2 |= 0x40400001;
		if(ADC1->SR & 0x2){
			analogValue = ADC1->DR;
		}
	}
}
