//PC0-PC7 -> D0-D7
//PB5 -> RS
//PB6 -> RW
//PB7 -> EN

#include "stm32f4xx.h"                  // Device header

//preprocessor directives
#define RS 0x20 //0b00100000
#define RW 0x40 //0b01000000
#define EN 0x80 //0b10000000

//forward method declarations
void GPIO_init(void);
void LCD_init(void);
void LCD_command(unsigned char cmnd);
void delay_ms(int delay);
void LCD_data(unsigned char data);

int main(void){
	//Initialise the LCD
	LCD_init();
	//Do it forever
	while(1){
		//Print Hi and wait for 1000 ms
		LCD_data('H');
		LCD_data('i');
		delay_ms(1000);
		//Clear the screen
		LCD_command(0x01);
	}
}

void GPIO_init(void){
	//Enable GPIOB and GPIOC, 0b0110 in RCC AHB1ENR reg
	RCC->AHB1ENR |= 0x6;
	//Set PB5, PB6 and PB7 as output pins
	GPIOB->MODER |= 0x5400;
	//Set EN and RW pins at LOW state
	GPIOB->BSRR = 0x00C;
	//Set PC0 - PC7 as output mode pins
	GPIOC->MODER |= 0x00005555;
}

void LCD_init(void){
	//Initialise the PORTs
	GPIO_init();
	//Three times make the command for 8 bit 1 line 5x7 font matrix
	delay_ms(30);
	LCD_command(0x30);
	delay_ms(10);
	LCD_command(0x30);
	delay_ms(1);
	LCD_command(0x30);
	//Make the command for 8 bit 2 line 5x7 font matrix
	LCD_command(0x38);
	//Move cursor right
	LCD_command(0x06);
	//Clear the screen, move cursor to home position
	LCD_command(0x01);
	//Turn display on, blink cursor
	LCD_command(0x0F);
	
}
void LCD_command(unsigned char cmnd){
	//Clear RS ans RW pins
	GPIOB->BSRR = (RS | RW ) << 16;
	//Set the command into command reg
	GPIOC->ODR = cmnd;
	//Enable the screen
	GPIOB->BSRR = EN;
	//Wait for ms
	delay_ms(10);
	//Disable the screen
	GPIOB->BSRR = EN << 16;
}

void LCD_data(unsigned char data){
	//Set RS pin
	GPIOB->BSRR = RS;
	//Clear RS pin
	GPIOB->BSRR = RW << 16;
	//Set the data into data register
	GPIOC->ODR = data;
	//Enable the screen
	GPIOB->BSRR = EN;
	//Wait for ms
	delay_ms(0);
	//Disable the screen
	GPIOB->BSRR = EN << 16;
	
}

void delay_ms(int delay){
	//make the pseudodelay funtion, can be modified by using SysTick delay function
	for(; delay > 0; delay--){
		for(int i = 0; i < 3195; i++);
	}
}
