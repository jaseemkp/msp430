#include<msp430.h>
main()
{
	int i ;
	unsigned bit,lfsr = 0xACE1u;
	P1DIR = 0x040;	
	while(1)
	{
/********** taps :16   14  13  11 *************/
		bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1 ;
		lfsr = (lfsr >> 1) | (bit<< 15);
		P1OUT = lfsr;
		for(i=0;i<30000;i++);
	}
}
