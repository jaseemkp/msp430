/*
*MSP430 launchpad based 4bit lcd code..
*Assuming the clock is 1MHz..
*All delays are designed according to that...
*for eg: __delay_cycles(1000) => 1ms delay at 1MHz clock
*Otherwise use any delay routines, if available.
*Note:
In my previous codes, the initialization is not so perfect
because I deviated from the original specifications...
But those codes are at least working for me,, Any way,
now I am providing a better code which includes a
pseudo_8bit_cmd function since the LCD expects an 8 bit 
command at first, before entering to 4 bit mode...
 
-Connections:
RS -> P1.0
EN -> P1.1
D7 to D4  -> P1.7 to P1.4
R/W to GROUND
 
-Compiler used: msp430-gcc
-Command line: msp430-gcc -mmcu=msp430g2231 lcd.c -mdisable-watchdog
-Burning code: sudo mspdebug rf2500
> prog a.out
> run
 
*/
 
#include<msp430g2231.h>
 
#define RS(X)     P1OUT = ((P1OUT & ~(BIT0)) | (X))
#define EN(X)   P1OUT = ((P1OUT & ~(BIT1)) | (X<<1))
#define LCD_STROBE do{EN(1);EN(0);}while(0)
#define databits P1OUT  // P1.7 - D7, ....., P1.4 - D4
#define LINE1 cmd(0x80)
#define LINE2 cmd(0xc0)
 
void port_init()
{
    P1OUT = 0 ;
    P1DIR = 0xff;
}
 
void data(unsigned char c)
{
    RS(1);
    __delay_cycles(40);  //40 us delay
    databits = (databits & 0x0f) | (c & 0xf0);
    LCD_STROBE;
    databits = (databits & 0x0f) | (c << 4) ;
    LCD_STROBE;
}
 
void cmd(unsigned char c)
{
    RS(0);
    __delay_cycles(40); //40 us delay
    databits = (databits & 0x0f) | (c & 0xf0);
    LCD_STROBE;
    databits = (databits & 0x0f) | (c << 4) ;
    LCD_STROBE;
}
 
void pseudo_8bit_cmd(unsigned char c)
{
    RS(0);
    __delay_cycles(15000); //15 ms delay
    databits = (c & 0xf0);
    LCD_STROBE;
}
void clear(void)
{
    cmd(0x01);
    __delay_cycles(3000); //3 ms delay
}
 
void lcd_init()
{
    pseudo_8bit_cmd(0x30); //this command is like 8 bit mode command
    pseudo_8bit_cmd(0x30); //lcd expect 8bit mode commands at first
    pseudo_8bit_cmd(0x30); //for more details, check any 16x2 lcd spec
    pseudo_8bit_cmd(0x20);
    cmd(0x28);             //4 bit mode command started, set two line
    cmd(0x0c);             // Make cursorinvisible
    clear();               // Clear screen
    cmd(0x6);              // Set entry Mode(auto increment of cursor)
}
 
void string(char *p)
{
    while(*p) data(*p++);
}
 
int main()
{
    port_init();
    lcd_init();
    LINE1;
    string("WELCOME TO");
    LINE2;
    string("MSP430 LAUNCHPAD");
    while(1);
}
