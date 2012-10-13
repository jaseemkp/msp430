#include <msp430.h>
#define LED_0 BIT0
__attribute__((interrupt(TIMERA1_VECTOR)))
timer_isr(void)
{
P1OUT ^= LED_0;
TACTL &= ~TAIFG;
while(1);

}
void main(void)
{
P1OUT = 0;
P1DIR = LED_0;
TACTL = TASSEL_2 | MC_2 | ID_3 | TAIE;
__enable_interrupt();
while(1);
}
