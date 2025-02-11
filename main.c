#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "ADC/ADC.h"
#include "LCD/LCD.h"

uint8_t sensor3 = 0;
char buffer[16];
void setup(){
	initADC();
	
	initUART9600();
	
	initLCD8bits();
	
	LCD_Set_Cursor(1, 0);
	LCD_String("S1:");
	LCD_Set_Cursor(6, 0);
	LCD_String("S2:");
	LCD_Set_Cursor(11, 0);
	LCD_String("S3:");
}

int main(void)
{
	setup();
	 while (1)
	 {
		 
		 uint16_t pot1 = readADC(6);
		 uint16_t pot2 = readADC(7);
		 float num = (pot1 / 255.0) * 5.0;// se multiplica por 5 por el voltaje que proporcionamos y que sea acorde y proporcional a lo que estamos haciedno
		 float num2 = (pot2 / 255.0) * 5.0;

		 // pot1
		 LCD_Set_Cursor(0, 1);
		 // conversión 
		 dtostrf(num, 4, 2, buffer);
		 //se pone 
		 LCD_String(buffer);
		 LCD_String(" "); // Borra posibles residuos   
	

		 // pot2
		 LCD_Set_Cursor(5, 1);
		 //conversión
		 dtostrf(num2, 4, 2, buffer);
		 LCD_String(buffer);
		LCD_String(" "); // Borra posibles residuos

		 
		 //contador del UART
		 LCD_Set_Cursor(11, 1);
		 //conversión de valores
		 itoa(sensor3, buffer, 10);
		 //se pone
		 LCD_String(buffer);
		LCD_String("   "); // Borra posibles residuos en caso de reducción de dígitos
		 if (UCSR0A & (1 << RXC0)){
			 char text = recieveUART();
			  if (text == '+') {
				  if (sensor3 < 255) sensor3++; 
			  }
			  else if (text == '-') {
				  if (sensor3 > 0) sensor3--;
			  }
			 
		 }

		 
		 

	 }
	}
