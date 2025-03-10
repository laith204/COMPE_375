/*
 * lab 5.c
 *
 * Created: 10/13/2024 9:00:22 PM
 * Author : Laith
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>

void port_init(){
	DDRD |= 0xF0; //turns bits 4-7 to 1 (outputs)
	DDRB &= 0xF0; //turns bits 0-3 to 0. (inputs)
	PORTB |= 0x0F;//turns pull up resistor on the chosen input bits (0-3).
	DDRC |= 0x10; //turns bit 4, port c to output. 
}
 
void timer_init(){
	TCCR0A |= (1<<WGM01); //turns ctc mode on
	TCCR0B |= (1 << CS02) | (1 << CS00); //prescaler = 1024.. 
	OCR0A = 70; //71 steps with ps = 1024, = 45.45ms... 50% of this = ~23ms, max Ton 
	OCR0B = ((70 + 1) / 2) - 1; //50% duty cycle.. will be on for half a ms, off for the other half.. 
}

int main(void)
{
	port_init(); //initializes the ports
	timer_init(); //initializes the timer
	int i, j;
	uint8_t Ton[4][4] = { //values for OCR0A in steps - 1.. calculated outside of this code..
		{70, 66, 62, 59},
		{55, 52, 49, 46},
		{43, 41, 39, 37},
		{35, 33, 31, 29}
	};
	while(1){
		for(i = 4; i < 8; i++){ // i = rows, port d (4-7)
			PORTD &= ~(1<<i); //sets a single row to logic 0 to see if that row is pressed
			for (j = 0; j < 4; j++){ //j = columns, port b (0-3)
				if(!(PINB & (1<<j))){ //if that column reads a logic 0, that means the row and column switch (keypad button) is pressed
					OCR0A = Ton[i-4][j];
					OCR0B = ((Ton[i-4][j] + 1) / 2) - 1; //50% duty cycle
				}
			}
			PORTD |= (1<<i); // sets that row that was set to logic 0 back to logic 1 so it can then check another row
		}
		PORTC |= (1<<4); //turns PORTC bit 4 to logic 1
		while ( (TIFR0 & (1 << OCF0B) ) == 0){} // wait for OCR0B overflow event
		TIFR0 |= (1 << OCF0B); // reset OCR0B overflow flag
		PORTC &= ~(1<<4); //turns PORTC bit 4 to logic 0
		while ( (TIFR0 & (1 << OCF0A) ) == 0){} // wait for OCR0A overflow event
		TIFR0 |= (1 << OCF0A); // reset OCR0A overflow flag
	}
}
