#include<LPC21XX.H>
#include"delay.h"
typedef unsigned char u8;
typedef unsigned int u32;
#define LCD_pins 0xFF
#define RS 1<<8
#define E 1<<9
void LCD_INIT(void);
void LCD_COMMAND(u8);
void LCD_DATA(u8);
void LCD_STRING(char *);
void LCD_STRING_CAROUSEL(char *,u32);
void LCD_INIT(void)
{
 IODIR0=LCD_pins|RS|E;
 LCD_COMMAND(0x0C);
 LCD_COMMAND(0x38);
 LCD_COMMAND(0x01);
 LCD_COMMAND(0x02);
 LCD_COMMAND(0x80);
}
void LCD_COMMAND(u8 cmd)
{
 IOPIN0=((0xffffff00)& IOPIN0)|cmd;
 IOCLR0=RS;
 IOSET0=E;
 ms_delay(5);
 IOCLR0=E;
}
void LCD_DATA(u8 d)
{
 IOPIN0=((0xffffff00)& IOPIN0)|d;
 IOSET0=RS;
 IOSET0=E;
 ms_delay(5);
 IOCLR0=E;
}
void LCD_STRING(char * str)
{  
while(*str)
  	 LCD_DATA(*str++);
}	

void LCD_STRING_CAROUSEL(char *str,u32 dp)
{ 	
	//char *lstr;
	//lstr=str;
    //while(*lstr)
	// slen++;

	/*while(*str && (dp+spos<0x90))
	 {LCD_DATA(*str++);
	  spos++;}*/

	//if(dp+spos>=90)
	//LCD_CMD(0x80);
	
	while(*str)
	{LCD_DATA(*str++);
	
	dp++;
	
	if(dp==0x90)
	LCD_COMMAND(0x80);}
}
 








	

