#include<msp430.h>
#define LED1 BIT0

__attribute__((interrupt(WDT_VECTOR)))
void isr()
{
	P1OUT ^= LED1;
}
//initialize watchdog as interval timer
void watchdog_init()
{
 // clk=smclk/32786,interval timer mode
 //wdt enabled (ie,WDTHOLD = 0)	
WDTCTL = WDTPW|WDTTMSEL;
	IE1 = WDTIE;
}
main()
{
	P1DIR = LED1;
	__enable_interrupt();
	watchdog_init();
	while(1);
}
