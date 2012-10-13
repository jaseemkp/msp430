#include<msp430.h>
#define LED1 BIT0
#define LED2 BIT6
void adc_init()
{
	ADC10CTL0 = ADC10ON | ADC10SHT_2 | SREF_0;
        ADC10CTL1 = INCH_4 | SHS_0 | ADC10DIV_0 | ADC10SSEL_0 | CONSEQ_0 ;
        ADC10AE0 = BIT4;
	ADC10CTL0 |= ENC ;
}
void start_conversion()
{
	ADC10CTL0 |= ADC10SC;
}

unsigned int converting()
{
	return ADC10CTL1 & ADC10BUSY;
}
void delay(int n)
{
	while(n--);
}
void main()
{
	P1DIR = LED1|LED2;
	P1OUT = 0x0;
	adc_init();
	while(1)
	{
		start_conversion();
		if(!converting())
		{
			if(ADC10MEM>767)		/***Check whether the voltage is in between 2.7 and 3.6V*****/
				P1OUT = LED1|LED2;
			else if(ADC10MEM>511)   /****checking whether the voltage level is in between 1.8 and 2.7******/
				P1OUT = LED1;
			else if(ADC10MEM>255)  /***checking whether the voltage is in between 0.9 & 1.8 **/
				P1OUT = LED2;
			else					/****checking whether the voltage is in between 0 and 0.9 *****/
				P1OUT = 0x00;
		}
		delay(30000);
	}

}	
