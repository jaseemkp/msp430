#include<msp430.h>
void delay()
{
	int i;
	for(i=0;i<30000;i++);
}
void main()
{
	P1DIR = 0xf;
	while(1)
	{
		P1OUT = 0x1;
		delay();
		P1OUT = 0x2;
		delay();
		P1OUT = 0x4;
		delay();
		P1OUT = 0x8;
		delay();
	}
}

