#include <msp430.h>
void main(void)
{
WDTCTL = WDTPW + WDTHOLD;
P1DIR = 0;

while(1)
{
if((0x08&P1IN))P1OUT|=0x01;
else P1OUT&=~0x01;
}
}
