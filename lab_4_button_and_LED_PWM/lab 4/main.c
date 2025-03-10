/*
 * lab 4.c
 *
 * Created: 10/1/2024 4:37:39 PM
 * Author : Laith
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#define LEDON PORTB |= (1<<5)
#define LEDOFF PORTB &= ~(1<<5)


void pwm(){
	TCCR0B |= (1<<2);
	TCCR0B |= (1<<0); //makes ps = 1024, 16384us per cycle = 0.016384s
	TCCR0A |= (1<<1); //turns ctc mode on in timer 0.
	OCR0A  = 156;	  //
	OCR0B = 0; 
}

int main(void)
{
    DDRB &= ~(1<<7); //turns pin 7 into an input
	DDRB |= (1<<5); //turns the led ouput port on 
	PORTB &= ~(1<<7); //turns off pull up resistor on pin 7 port b... the switch is connected to ground when depressed
	pwm();
    while (1) 
    {
		if (!(PINB & 1<<7)){ //checks if the button is pressed
				if (OCR0B < (OCR0A-1)){
					OCR0B++;
					LEDON;
					while ( !(TIFR0 & (1 << OCF0B) )){} // wait for OCR0B overflow event
					TIFR0 |= (1 << OCF0B); // reset OCR0B overflow flag
				}
				if(OCR0B == (OCR0A-1)){
					LEDON;
					while(!(PINB & 1<<7)){}
				} else {
					LEDOFF;
					while ( !(TIFR0 & (1 << OCF0A) )){} //waits for overflow event
					TIFR0 |= (1 << OCF0A); // reset the overflow flag
				}
		} else {
				if (OCR0B > 0){
					OCR0B--;
					LEDON;
					while ( (TIFR0 & (1 << OCF0B) ) == 0){} // wait for OCR0B overflow event
					TIFR0 |= (1 << OCF0B); // reset OCR0B overflow flag
					LEDOFF;
					while ( (TIFR0 & (1 << OCF0A) ) == 0){} //waits for overflow event
					TIFR0 |= (1 << OCF0A); // reset the overflow flag
				}
			}
    }
}
