/*
 * lab 2 compe375.c
 *
 * Created: 9/12/2024 6:45:09 PM
 * Author : laith
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#define BAUD 9600 // define baud
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1) // set baud rate

void uart_init (void)
{
	UBRR0H &= 0;
	UBRR0H = (BAUDRATE>>8); // shift the register right by 8 bits
	UBRR0L = BAUDRATE; // set baud rate
	UCSR0B|= (1<<TXEN0); // enable transmitter
	//UCSR0C|= (1<<UCSZ00)|(1<<UCSZ01); // 8bit data format
	//UCSR0C &= ~(1<<UPM0)|~(1<<UPM1); //no parity
	//above 2 lines not needed because they start at 0 parity, and it is set at 8 bits //automatically.
	//UCSR0C &= ~(1<<USBS); //sets stop bits to 1 only… usbs = 0 now... 0 = 1 stop bit
	//dont need above line because it starts off at 0.. Dont have to manually set it.
}

void uart_transmit (unsigned char data) {
	while (!( UCSR0A & (1<<5))){} // wait while register is free
	UDR0 = data; // load data in the register
}


int main(void)
{
	uart_init();
	char RedId[] = "828440295\n\r";
	int i;
	while(1){
		for(i = 0; i < sizeof(RedId); i++) {
			while(!(UCSR0A & (1<<5)));
				UDR0 = RedId[i];
		}
		_delay_ms(500);
	}
}
