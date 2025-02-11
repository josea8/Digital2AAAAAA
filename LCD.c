
#include "LCD.h"


void initLCD8bits(){
	/* 
	D0 - PD2,D5- PD7, 
	D6 - PB0
	D7 - PB1
	RS - PB2
	E  - PB3
	*/
	DDRD |= (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7);
	DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB3);
	_delay_ms(50);
	
	// MO8 BITS
	LCD_CMD(0x38);	
	_delay_ms(5);	
	LCD_CMD(0x0C);	
	_delay_ms(5);
	LCD_CMD(0x06);	
	_delay_ms(5);
	// limpia el display
	LCD_CMD(0x01);	
	_delay_ms(5);
	
	
}

void LCD_Port(char a){
	// PINES DE LA PANTALLA
	// D0-D5
	PORTD = (PORTD & 0x03) | ((a & 0x3F) << 2);
	// D6-D7
	PORTB = (PORTB & 0xFC) | ((a >> 6) & 0x03);
	_delay_ms(10);
}
void LCD_CMD(uint8_t cmd){
	
	PORTB &= ~(1 << PB2);
	LCD_Port(cmd);
	
	
	PORTB |= (1 << PB3);
	_delay_ms(6);
	
	
	PORTB &= ~(1 << PB3);
}
void LCD_WRT(uint8_t data){
	
	PORTB |= (1 << PB2);
	LCD_Port(data);	
	
	PORTB |= (1 << PB3);
	_delay_ms(4);
	
	PORTB &= ~(1 << PB3);
}
void LCD_String(char *str){
	while (*str) {
		LCD_WRT(*str);
		str++;
	}
}
void LCD_Set_Cursor(char x, char y){
	char pos = (y == 0) ? (0x80 + x) : (0xC0 + x);
	LCD_CMD(pos);
}
