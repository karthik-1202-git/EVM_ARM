#include <lpc21xx.h>
#include "lcd.h"

#define c0 (IOPIN0 & (1<<20))
#define c1 (IOPIN0 & (1<<21))
#define c2 (IOPIN0 & (1<<22))
#define c3 (IOPIN0 & (1<<23))

#define r0 (1<<16)
#define r1 (1<<17)
#define r2 (1<<18)
#define r3 (1<<19)

unsigned char keypad[4][4] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

unsigned char key(void)
{
    unsigned char row, col;

    IODIR0 |= r0 | r1 | r2 | r3;  // rows as output
    //Pins are set to default so no configuration needed for Columns

    while(1)
    {
        IOCLR0 |= r0 | r1 | r2 | r3; // clear all rows
        IOSET0 |= c0 | c1 | c2 | c3; // set all columns HIGH
	
	while((c0&&c1&&c2&&c3)==1);
        // scan row 0
        IOCLR0 = r0;
        IOSET0 = r1 | r2 | r3;
        if(!(c0 && c1 && c2 && c3))
        {
            row = 0;
            break;
        }

        // scan row 1
        IOCLR0 = r1;
        IOSET0 = r0 | r2 | r3;
        if(!(c0 && c1 && c2 && c3))
        {
            row = 1;
            break;
        }

        // scan row 2
        IOCLR0 = r2;
        IOSET0 = r0 | r1 | r3;
        if(!(c0 && c1 && c2 && c3))
        {
            row = 2;
            break;
        }

        // scan row 3
        IOCLR0 = r3;
        IOSET0 = r0 | r1 | r2;
        if(!(c0 && c1 && c2 && c3))
        {
            row = 3;
            break;
        }
    }

    // Detect which column is LOW
    if(!c0)
        col = 0;
    else if(!c1)
        col = 1;
    else if(!c2)
        col = 2;
    else
        col = 3;

    ms_delay(250); // debounce
    while(!(c0 && c1 && c2 && c3)); // wait until key released

    return keypad[row][col];
}

int main()
{
    char res;
    lcd_init();
    lcd_command(0x80);
    lcd_str("4x4 KEYPAD");

    while(1)
    {
        res = key();
        lcd_command(0x01); // clear screen
        lcd_command(0x80);
        lcd_str("Key:-");
        lcd_command(0xC0);
        lcd_data(res); // directly display char
        ms_delay(500);
    }
}
