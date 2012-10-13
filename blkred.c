#include <msp430.h>

void main(void)
{
int i;
P1DIR = 0x40;
while (1)
	{


P1OUT ^= 0x40;
for (i=1; i<30000; i=i+1) {}
}
}
