#include <msp430.h>
main()
{
	P1DIR=0x01;
	P1OUT=0x01;
	TACTL=0x02E0;

while(1){
	while(!(TACTL&1 ));
	TACTL^=1;
	P1OUT^=1;
	}
}
