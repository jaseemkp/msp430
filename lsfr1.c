#include<msp430.h>
main()
{
	int i;
	unsigned lfsr = 0xACE1u;
	P1DIR = 0x040;
	while(1)
	{
		lfsr = (lfsr >> 1)^(-(lfsr & 1u) & 0xB400u);
		P1OUT = lfsr;
		for(i=0;i<30000;i++);
	}
}
