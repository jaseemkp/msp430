/*******Here I'm use common anod 7 segment display*************/
#include<msp430.h>
void delay()
{
	int i;
	for(i=0;i<30000;i++);
}
void main()
{
	P1DIR =0xff;
	while(1)
	{
		P1OUT =0xf9;
		delay();
		P1OUT =0xa4;
		delay();
		P1OUT =0xb0;
		delay();
		P1OUT =0x99;
		delay();
		P1OUT =0x92;
		delay();
		P1OUT =0xc2;
		delay();
		P1OUT =0xb8;
		delay();
		P1OUT =0x00;
		delay();
		P1OUT =98;
		delay();
	}
}
