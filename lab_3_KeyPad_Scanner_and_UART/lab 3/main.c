/*
 * lab 3.c
 *
 * Created: 9/19/2024 4:36:55 PM
 * Author : laith
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#define BAUD 9600 // define baud
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1) // set baud rate

void uart_init (void)
{
	UBRR0H &= 0; //clears the register. not needed since its 0 from the start
	UBRR0H = (BAUDRATE>>8); // shift the register right by 8 bits
	// above line not needed for baud rate of 9600, and cpu frequency above of 16Mhz.
	UBRR0L = BAUDRATE; // set baud rate
	UCSR0B|= (1<<TXEN0); // enable transmitter
	UCSR0C|= (1<<UCSZ00)|(1<<UCSZ01); // 8bit data format
	UCSR0C &= ~(1<<4)|~(1<<5); //no parity, when bits 4 and 5 are 0, parity is disabled
	//above 2 lines not needed because they start at 0 parity, and it is set at 8 bits //automatically.
	UCSR0C &= ~(1<<USBS0) | (1<<USBS1); //sets stop bits to 1 only… usbs = 0 now.. 0 = 1 stop bit
	//dont need above line because it starts off at 0.. Dont have to manually set it.
}

void uart_transmit (unsigned char data) {
	while (!( UCSR0A & (1<<5))){}; // wait while register is free
	UDR0 = data; // load data in the register
}

void port_init(){
	DDRD |= 0xF0; //turns bits 4-7 to 1 (outputs)
	DDRB &= 0xF0; //turns bits 0-3 to 0. (inputs)
	PORTB |= 0x0F;//turns pull up resistor on the chosen input bits (0-3).
}

int main(void)
{
	port_init(); //initializes the ports
	uart_init(); //initializes the usart protocol values
	char keyPad[4][4] = {
		{'D', '#', '0', '*'},
		{'C', '9', '8', '7'},
		{'B', '6', '5', '4'},
		{'A', '3', '2', '1'}
	};
	int i, j;
	while(1){
		for(i = 4; i < 8; i++){ // i = rows, port d (4-7)
			PORTD &= ~(1<<i); //sets a single row to logic 0 to see if that row is pressed
			for (j = 0; j < 4; j++){ //j = columns, port b (0-3)
				if(!(PINB & (1<<j))){ //if that column reads a logic 0, that means the row and column switch (keypad button) is pressed
					uart_transmit(keyPad[(i-4)][j]); //transmits the keypad button that is pressed
					while(!(PINB & (1<<j))){} //busy while that will stop the program from moving on until the keypad button is released 
				}
			}
			PORTD |= (1<<i); // sets that row that was set to logic 0 back to logic 1 so it can then check another row
		}
	}
}