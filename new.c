#include <msp430.h>

int main(void) {
    
    /* Configure pins 0 on port 1 as output pins */
    P1DIR = BIT0;

    /* a flag to tell us when we've handled a button event */
    int buttonPushed = 0;

    /* we'll toggle between different modes */
    int blinkMode = 0;

    /* which lights we need to blink -- start red only */
    int blinkMask = BIT0;

    /* infinite loop */
    for( ; ; ) {
        int j;
        /* delay while watching for button presses */
        for( j = 0; j < 100; j++ ) {
            /* The following two lines implement a very crude delay loop.
             * The actual length of the delay can vary significantly.
             * This approach may not work with all compilers.
             */
            volatile int i;
            for( i = 0; i < 200; i++ );

            /* Switch 1 is connected to pin 3.  If it is low, then change the
             * blinking behavior (unless it we have handled the press already)
             */
            if(( P1IN & BIT3 ) == 0 ) {
              
                        /* blink red (bit 0) only */
                        blinkMask = BIT0;
                    } else if( blinkMode == 1 ) {
                        
                        /* make sure red (pin 0) is off */
                        P1OUT &= ~BIT0;
                   
                    } else {
                        /* blink both alternately */
                        blinkMask = BIT0 + BIT6;

                        /* make sure red is off and green is on */
                        P1OUT &= ~BIT0;
                        P1OUT |= BIT6;
                    }
                }
            } else {
                buttonPushed = 0;
            }

       
    }
}

