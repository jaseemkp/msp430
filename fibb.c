#include<msp430.h>
#define Delay(k) for(i=0;i<k;i++)
void main()
{
	int i;
	unsigned bit;
	unsigned b;
	WDTCTL = WDTPW + WDTHOLD;
	P1DIR=0x41;
        b=0x002d;
        P1OUT=b;
	while(1){
		bit=((P1OUT>>0)^(P1OUT>>2)^(P1OUT>>5)^(P1OUT>>3))&1;
		P1OUT=(P1OUT>>1)|(bit<<15);
		Delay(30000);
	}
}
