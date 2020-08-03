//ADC is used for reading potentiometer value 
//POT value is stored in the variable and depends on
//that value, SysTick Timer is causing delay
//PA1 is connected to pot and PA5 is connected to the LED
//LED is indicating the amount of delay 

#include "stm32f4xx.h"                  // Device header

//forward method declarations
void GPIOA_init(void);
void ADC_init(void);
int ADC_read(void);
void delay_ms(int ch);

//global system variable declarations
int analogValue = 0;

int main(void){
	//Initialise GPIOA and ADC1 module
	GPIOA_init();
	ADC_init();
	//Do it forever
	while(1){
		//Read ADC value, store it in the global variable 
		//Stop program execution depending on ADC value
		//Toggle the LED
		analogValue = ADC_read();
		delay_ms(analogValue);
		GPIOA->ODR ^= 0x20;
	}
}
void GPIOA_init(void){
	//Enable clock access to GPIOA 
	RCC->AHB1ENR |= 0x1;
	//Declare PA5 as output mode pin
	GPIOA->MODER |= 0x400;
}
void ADC_init(void){
	//Enable access to GPIOA module
	RCC->AHB1ENR |= 0x1;
	//Declare PA1 as analog input mode pin
	GPIOA->MODER |= 0xC;
	//Enable clock access to ADC1 module
	RCC->APB2ENR |= 0x100;
	//Disable ADC1
	ADC1->CR2 = 0;
	//Set the first sequence at ADC1 CH1
	ADC1->SQR3 |= 0x1;
	//Enable th ADC1 module
	ADC1->CR2 |= 0x1;
}

int ADC_read(void){
	//Start AD conversion
	ADC1->CR2 |= 0x40000000;
	//Wait while ADC buffer is not full
	while(!(ADC1->SR & 0x2)){}
	return ADC1->DR;
}

void delay_ms(int ch){
	//Define SysTick registers
	SysTick->LOAD = 16000 - 1;
	SysTick->VAL = 0;
	SysTick->CTRL = 0x5;
	for(int i = 0; i < ch; i++){
		while((SysTick->CTRL & 0x10000) == 0){}
	}
}
