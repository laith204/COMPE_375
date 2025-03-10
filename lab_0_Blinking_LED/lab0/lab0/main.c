/*
 * lab0.c
 *
 * Created: 9/7/2024 9:11:03 AM
 * Author : laith
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    /* Replace with your application code */
	DDRB |= (1<<DDB5);
    while (1) 
    {
		PORTB |= (1<<PORTB5);
		_delay_ms(1000);
		PORTB &= ~(1<<PORTB5);
		_delay_ms(1000);
    }
}

