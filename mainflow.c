#include "lcd.h"
#include<LPC21XX.H>
const unsigned char cgram_lut[4][8] = {
    {0x00, 0x0A, 0x1F, 0x1F, 0x1F, 0x0E, 0x04, 0x00}, // Heart
    {0x00, 0x0A, 0x00, 0x00, 0x11, 0x0E, 0x00, 0x00}, // Smiley
    {0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x04, 0x00}, // Bell
    {0x1F, 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x1F, 0x00}  // Hourglass
};

void CGRAM_WRITE(void);
void display_cuschar(void);
int main()
{
	LCD_INIT();
	ms_delay(5);
	CGRAM_WRITE();
	LCD_COMMAND(0x80);
//LCD_STRING("DEI PRINT PLS");
    display_cuschar();
    	while(1);
}

void CGRAM_WRITE(void)
{	   int i,j;
  for (i = 0; i < 4; i++) {
        LCD_COMMAND(0x40 + (i * 8)); // Set CGRAM address
        for (j = 0; j < 8; j++) {
            LCD_DATA(cgram_lut[i][j]);
        }
    }
}

void display_cuschar(void)
{
	LCD_COMMAND(0x80); // Set cursor to line 1, position 0

    	LCD_DATA(0x00); // Heart
    	LCD_DATA(' ');
    	LCD_DATA(' ');

    	LCD_DATA(0x01); // Smiley
    	LCD_DATA(' ');
    	LCD_DATA(' ');

    	LCD_DATA(0x02); // Bell
    	LCD_DATA(' ');
    	LCD_DATA(' ');

    	LCD_DATA(0x03);//HourGlass
}




