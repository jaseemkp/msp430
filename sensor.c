#include<msp430.h>

void adc_init()
{
	ADC10CTL0 = ADC10ON | ADC10SHT_2 | SREF_0;
	ADC10CTL1 = INCH_0 | SHS_0 | ADC10DIV_0 | ADC10SSEL_0 | CONSEQ_0 ;
	ADC10AE0 = BIT0;
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
void main()
{	
	int i;
	P1DIR=0x40;
	P1OUT=0x0;
	adc_init();
	
	while(1){
		start_conversion();
		if(!converting())
			P1OUT=(ADC10MEM<0x17C)?0x40:0;
	for(i=0;i<10000;i++);
	}
}	
