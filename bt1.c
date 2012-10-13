#include <msp430.h>

#define pin0mask  (0x01 << 0)
#define pin3mask  (0x01 << 3)


int main(void) {
    /* Hold the watchdog timer so it doesn't reset our chip */
    WDTCTL = WDTPW + WDTHOLD;

    /* Configure pins 0on port 1 as output pins */
    P1DIR = 0x00;

    /* Set pin 6 high.  Basically, this command sets any combination
     * of the pins on port 1 high.  Pin 0 is 2^0, pin 1 is 2^2, etc.
     * Values can be binary or'd together. Other pins are low.
     */
    P1OUT = 0x01;

    /* infinite loop */
    for( ; ; ) {
        /* The following two lines implement a very crude delay loop.
         * The actual length of the delay can vary significantly.
         * This approach may not work with all compilers.
         */
        volatile int i;
        for( i = 0; i < 20000; i++ );

        /* Switch 2 is connected to pin 3.  If it is low, then change the
         * blinking behavior.  Sometimes we blink both LEDs, sometimes only
         * the red LED.
         */
        if(( P1IN & pin3mask ) == 0 ) {
            /* Toggle just pin 0. */
            P1OUT ^= 0x01;
        } else {
            /* Toggle both pin 0 and pin 6 */
            P1OUT ^= 0x01;
        }
    }
}

