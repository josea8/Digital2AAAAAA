/*
 * UART.c
 *
 * Created: 10/02/2025 19:54:40
 *  Author: José Velásquez
 */ 
#include "UART.h"

void writeUART(char Caracter){
	while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = Caracter;
}

void WriteTextUART(char * Texto){
	uint8_t i;
	for (i=0; Texto[i]!= '\0'; i++){
		while (!(UCSR0A & (1<<UDRE0)) );
		UDR0 = Texto[i];
	}
}

void initUART9600(){

	DDRD &= ~(1<<DDD0);
	DDRD |= (1<<DDD1);
	
	UCSR0A = 0;
	
	//configurar UCSR0B  
	UCSR0B = 0;
	UCSR0B |= (1<<RXCIE0) | (1<<RXEN0) | (1<<TXEN0);

	UCSR0C = 0;
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
	//valor de baudrate: 9600
	UBRR0 = 103;
}

uint8_t recieveUART(void){
	while (!(UCSR0A & (1 << RXC0)));
	return UDR0;
}