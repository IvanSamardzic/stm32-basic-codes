// Read the ADC data register value
// Set pot middle pin on PA0

#include "stm32f4xx.h"                  // Device header
int main(void){
	// Local variable definitions
	uint32_t analogValue;
	
	// Enable clock to GPIOA
	RCC->AHB1ENR |= 0x1;
	
	// Set PA1 as analog input pin and PA2, PA0 as output pin
	GPIOA->MODER |= 0x1D;
	
	// Enable clock to ADC1
	RCC->APB2ENR |= 0x100;
	
	// Disable ADC and set the sequence
	ADC1->CR2 = 0;
	ADC1->SQR3 = 1;
	
	// Enable ADC and declare continuous conversion mode
	ADC1->CR2 |= 0x3;
	
	while(1){
		// Start the conversion
		ADC1->CR2 |= 0x40000000;
		
		// Write result into a variable
		analogValue= ADC1->DR;
		
		// Check ADC1->ODR value
		if(ADC1->DR > 0x0800){
		
			// Turn on the LED
			GPIOA->ODR = 0x1;
		}
		if(ADC1->DR < 0x0800){
			GPIOA->ODR = 0x4;
		}
	}
}
