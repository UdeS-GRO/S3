/* Fonction de contrôle des moteurs

Marc Rousseau

*/


#include <LCD_LK162.h>

LCD_LK162::LCD_LK162(){ 
  
	
}

void LCD_LK162::LK_init(int port,int baud) {

 // initialize serial ports:
 if(port == 0)  Serial.begin(baud);
 if(port == 1)  Serial1.begin(baud);
 if(port == 2)  Serial2.begin(baud);
 if(port == 3)	Serial3.begin(baud);
 

}

void LCD_LK162::LK_print_pos(int port, char *p,char col, char row) {	// Envoi char à l'afficheur

	if(port == 0)
	{	Serial.write(LCD_ADDRESS);
		Serial.write(LCD_SET_CURSOR_POS);
		Serial.write(col);
		Serial.write(row);
		while(*p) Serial.write(*p++);

	}

	if(port == 1)
	{	Serial1.write(LCD_ADDRESS);
		Serial1.write(LCD_SET_CURSOR_POS);
		Serial1.write(col);
		Serial1.write(row);
		while(*p) Serial1.write(*p++);

	}

	if(port == 2)
	{	Serial2.write(LCD_ADDRESS);
		Serial2.write(LCD_SET_CURSOR_POS);
		Serial2.write(col);
		Serial2.write(row);
		while(*p) Serial2.write(*p++);

	}
	
	if(port == 3)
	{	Serial3.write(LCD_ADDRESS);
		Serial3.write(LCD_SET_CURSOR_POS);
		Serial3.write(col);
		Serial3.write(row);
		while(*p) Serial3.write(*p++);

	}
	
	

}

void LCD_LK162::LK_print(int port,char *p) {
	
	if(port == 0)
	{	
		while(*p) Serial.write(*p++);

	}

	if(port == 1)
	{	
		while(*p) Serial1.write(*p++);

	}

	if(port == 2)
	{	
		while(*p) Serial2.write(*p++);

	}

	if(port == 3)
	{	
		while(*p) Serial3.write(*p++);

	}
	
}

void LCD_LK162::LK_clear(int port) {

	if(port == 0)
	{	Serial.write(LCD_ADDRESS);
		Serial.write(LCD_CLEAR_SCREEN);
		
	}

	if(port == 1)
	{	Serial1.write(LCD_ADDRESS);
		Serial1.write(LCD_CLEAR_SCREEN);
		
	}

	if(port == 2)
	{	Serial2.write(LCD_ADDRESS);
		Serial2.write(LCD_CLEAR_SCREEN);
		
	}
	
	if(port == 3)
	{	Serial3.write(LCD_ADDRESS);
		Serial3.write(LCD_CLEAR_SCREEN);
	
	}
}

unsigned int LCD_LK162::LK_keypad(int port) {

	unsigned int inByte;

	if(port == 0)
	{
		if (Serial.available()) {
		inByte = Serial.read();
		}
		
	}

	if(port == 1)
	{
		if (Serial1.available()) {
		inByte = Serial1.read();
		}
		
	}

	if(port == 2)
	{
		if (Serial2.available()) {
		inByte = Serial2.read();
		}
		
	}

	if(port == 3)
	{
		if (Serial3.available()) {
		inByte = Serial3.read();
		}
		
	}
	return inByte;
    //Serial1.write(inByte);
  

}