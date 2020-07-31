//ADC is connected to clock via APB2
#include "stm32f4xx.h"                  // Device header
extern unsigned  int analogValue;

int main(void){
	// Enable clock access to GPIOA
	RCC->APB1ENR |= 0x1;
	// Declare PA1 as analog mode pin
	GPIOA->MODER |= 0xC;
	// Enable clock access to ADC1
	RCC->APB2ENR |= 0x100;
	// Disable ADC1 module
	ADC1->CR2 = 0;
	// Set the first conversion in regular sequence
	// ADC1 CH1 is being declared as input channel
	ADC1->SQR3 |= 0x1;
	// Enable ADC1 module
	ADC1->CR2 |= 1;  
	// Do it forever
	while(1){
		// Start conversion of regular channels
		ADC1->CR2 |= 0x40000000;
		// Wait while the end of conversion
		while(ADC1->SR & 2){
			// Write the ADC1 result into the global variable
			analogValue  = ADC1->DR;
		}
	}
}

