/*
 * lab 6.c
 *
 * Created: 10/29/2024 11:35:50 PM
 * Author : Laith
 */ 


#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#define LEDON  PORTB |= (1<<5);
#define LEDOFF PORTB &= ~(1<<5);

void port_init(){
	//keypad init
	DDRD |= 0xF0; //turns bits 4-7 to 1 (outputs)
	DDRB &= 0xF0; //turns bits 0-3 to 0. (inputs)
	PORTB |= 0x0F;//turns pull up resistor on the chosen input bits (0-3).
	DDRC |= 0x10; //turns bit 4, port c to output.
	
	//led init
	DDRB |= (1<<5); //turns port b pin 5 to output mode
}

void keypad_check(){
	int i, j;
	
	uint8_t Ton[4][4] = { //values for OCR0A in steps - 1.. calculated outside of this code..
		{21, 42, 63, 63},
		{84, 105, 126, 126},
		{147, 168, 189, 189},
		{189, 189, 189, 189}
	};
	
	for(i = 4; i < 8; i++){ // i = rows, port d (4-7)
		PORTD &= ~(1<<i); //sets a single row to logic 0 to see if that row is pressed
		for (j = 0; j < 4; j++){ //j = columns, port b (0-3)
			if(!(PINB & (1<<j))){ //if that column reads a logic 0, that means the row and column switch (keypad button) is pressed
				OCR0B = Ton[i-4][j] - 1;
			}
		}
		PORTD |= (1<<i); // sets that row that was set to logic 0 back to logic 1 so it can then check another row
	}
}

void timer0_init(){
	TCCR0A |= (1<<WGM01); //turns ctc mode on
	
	OCR0A = 187; //3ms period
	TIMSK0 |= (1<<OCIE0A) | (1<<OCIE0B); //enables compare match a & b interrupts
	
	TCCR0B |= (1 << CS02); //prescaler = 256.. and start timer
}

//828440295
//period is 3ms... scans the keypad
//pwm frequency = 600HZ = 1.67ms

void timer2_init(){
	TCCR2A |= (1 << WGM21); //turns ctc mode on
	
	OCR2A = 209; //1.672ms. as close as i can 
	TIMSK2 |= (1 << OCIE2A); //enables compare match a interrupt
	
	TCCR2B |= (1 << CS22) | (1 << CS20); //prescaler = 128.. and start timer
}

volatile uint8_t a = 0;

int main(void)
{
	
    port_init(); //initializes the ports
    timer0_init(); //initializes timer 0
	timer2_init(); //intializes timer 2
	sei();//turns interrupts on
	
    while (1) 
    {
		if (a > 0){
			keypad_check();
			a = 0;
		}
    }
}

ISR (TIMER0_COMPB_vect)
{
	LEDOFF;
}

ISR (TIMER0_COMPA_vect)
{
	LEDON;
}

ISR (TIMER2_COMPA_vect)
{
	//LEDON;
	a++;
}
