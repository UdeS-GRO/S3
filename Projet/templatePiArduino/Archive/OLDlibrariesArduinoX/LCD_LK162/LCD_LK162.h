/* Fonction de l'afficheur LCD 16x2

Marc Rousseau

*/

#include "Arduino.h"

#ifndef LCD_LK162_h
#define LCD_LK162_h

#define LCD_ADDRESS 254
#define LCD_SET_CURSOR_POS 71
#define LCD_CLEAR_SCREEN 88
#define LCD_DISPLAY_ON 66
#define LCD_DISPLAY_OFF 70


class LCD_LK162
{
  public:
    LCD_LK162();
    void LK_init(int port,int baud);
	void LK_print_pos(int port, char *p,char col, char row);	// Envoi char à l'afficheur
	void LK_print(int port,char *p);	// envoi char à l'afficheur sans position
//	void LCD03_code(unsigned char code);	// code clear, backlight...
	void LK_clear(int port);		// clears le display
//	void LK_textIP(char col, char row); // text insertion point col,row
//	void LK_backlight_ON(char min); // Backlight ON, minutes (0 = always)
//	void LK_backlight_OFF(void);
//	void LK_draw_image(char ref, char x, char y);
	unsigned int LK_keypad(int port);
    
};

#endif // Fonction de l'afficheur LCD 16x2