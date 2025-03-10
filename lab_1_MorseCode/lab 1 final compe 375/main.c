/*
 * lab1.c
 *
 * Created: 9/6/2024 8:48:54 AM
 * Author : loraha4821
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int i, j; 

void dot(){
	PORTB |= (1<<PORTB5);
	_delay_ms(200);
}


void dash(){
	PORTB |= (1<<PORTB5);
	_delay_ms(600);
}


void spc(int units){
	for (j = 0; j < units; j++){
		PORTB &= ~(1<<PORTB5);
		_delay_ms(200);     //spc btwn dot/dash of same letter is 1 unit
							//spc btwn different letters is 3 units
							//spc between words is 7 units
	}
}




void output(char input[], int size){
	//int same = 0; //if it is the same letter or number twice, is there a need for a space?
	//int space = 0;
	for(i = 0; i < size; i++){
		if(input[i] == 'a' || input[i] == 'A'){
			dot();spc(1);dash();
		} else if(input[i] == 'b' || input[i] == 'B'){
			dash();spc(1);dot();spc(1);dot();spc(1);dot();
		} else if(input[i] == 'c' || input[i] == 'C'){
			dash();spc(1);dot();spc(1);dash();spc(1);dot();
		} else if(input[i] == 'd' || input[i] == 'D'){
			dash();spc(1);dot();spc(1);dot();
		} else if(input[i] == 'e' || input[i] == 'E'){
			dot();
		} else if(input[i] == 'f' || input[i] == 'F'){
			dot();spc(1);dot();spc(1);dash();spc(1);dot();
		} else if(input[i] == 'g' || input[i] == 'G'){
			dash();spc(1);dash();spc(1);dot();
		} else if(input[i] == 'h' || input[i] == 'H'){
			dot();spc(1);dot();spc(1);dot();spc(1);dot();
		} else if(input[i] == 'i' || input[i] == 'I'){
			dot();spc(1);dot();
		} else if(input[i] == 'j' || input[i] == 'J'){
			dot();spc(1);dash();spc(1);dash();spc(1);dash();
		} else if(input[i] == 'k' || input[i] == 'K'){
			dash();spc(1);dot();spc(1);dash();
		} else if(input[i] == 'l' || input[i] == 'L'){
			dot();spc(1);dash();spc(1);dot();spc(1);dot();
		} else if(input[i] == 'm' || input[i] == 'M'){
			dash();spc(1);dash();
		} else if(input[i] == 'n' || input[i] == 'N'){
			dash();spc(1);dot();
		} else if(input[i] == 'o' || input[i] == 'O'){
			dash();spc(1);dash();spc(1);dash();
		} else if(input[i] == 'p' || input[i] == 'P'){
			dot();spc(1);dash();spc(1);dash();spc(1);dot();
		} else if(input[i] == 'q' || input[i] == 'Q'){
			dash();spc(1);dash();spc(1);dot();spc(1);dash();
		} else if(input[i] == 'r' || input[i] == 'R'){
			dot();spc(1);dash();spc(1);dot();
		} else if(input[i] == 's' || input[i] == 'S'){
			dot();spc(1);dot();spc(1);dot();
		} else if(input[i] == 't' || input[i] == 'T'){
			dash();
		} else if(input[i] == 'u' || input[i] == 'U'){
			dot();spc(1);dot();spc(1);dash();
		} else if(input[i] == 'v' || input[i] == 'V'){
			dot();spc(1);dot();spc(1);dot();spc(1);dash();
		} else if(input[i] == 'w' || input[i] == 'W'){
			dot();spc(1);dash();spc(1);dash();
		} else if(input[i] == 'x' || input[i] == 'X'){
			dash();spc(1);dot();spc(1);dot();spc(1);dash();
		} else if(input[i] == 'y' || input[i] == 'Y'){
			dash();spc(1);dot();spc(1);dash();spc(1);dash();
		} else if(input[i] == 'z' || input[i] == 'Z'){
			dash();spc(1);dash();spc(1);dot();spc(1);dot();
		} else if(input[i] == '1'){
			dot();spc(1);dash();spc(1);dash();spc(1);dash();spc(1);dash();
		} else if(input[i] == '2'){
			dot();spc(1);dot();spc(1);dash();spc(1);dash();spc(1);dash();
		} else if(input[i] == '3'){
			dot();spc(1);dot();spc(1);dot();spc(1);dash();spc(1);dash();
		} else if(input[i] == '4'){
			dot();spc(1);dot();spc(1);dot();spc(1);dot();spc(1);dash();
		} else if(input[i] == '5'){
			dot();spc(1);dot();spc(1);dot();spc(1);dot();spc(1);dot();
		} else if(input[i] == '6'){
			dash();spc(1);dot();spc(1);dot();spc(1);dot();spc(1);dot();
		} else if(input[i] == '7'){
			dash();spc(1);dash();spc(1);dot();spc(1);dot();spc(1);dot();
		} else if(input[i] == '8'){
			dash();spc(1);dash();spc(1);dash();spc(1);dot();spc(1);dot();
		} else if(input[i] == '9'){
			dash();spc(1);dash();spc(1);dash();spc(1);dash();spc(1);dot();
		} else if(input[i] == '0'){
			dash();spc(1);dash();spc(1);dash();spc(1);dash();spc(1);dash();
		} else if(input[i] == ' '){
			spc(4); //4 +3 = 7 delay
		}
		spc(3);
	}
	spc(20);
}


int main(){
	DDRB |= (1<<DDB5);
	char yes[] = "Laith Oraha 828440295";
	int size = sizeof(yes);
	while(1){
		output(yes, size);
	}
	return 0;
}