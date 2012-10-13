#include<msp430g2231.h> 
#define RS(X)     P1OUT = ((P1OUT & ~(BIT0)) | (X))
#define EN(X)   P1OUT = ((P1OUT & ~(BIT1)) | (X<<1))
#define LCD_STROBE do{EN(1);EN(0);}while(0)
#define databits P1OUT  // P1.7 - D7, ....., P1.4 - D4
#define LINE1 cmd(0x80)
#define LINE2 cmd(0xc0)
 
void port_init()
{
    P1OUT = 0 ;
    P1DIR = 0xff;
}
 
void data(unsigned char c)
{
    RS(1);
    __delay_cycles(40); 
    databits = (databits & 0x0f) | (c & 0xf0);
    LCD_STROBE;
    databits = (databits & 0x0f) | (c << 4) ;
    LCD_STROBE;
}
 
void cmd(unsigned char c)
{
    RS(0);
    __delay_cycles(40); //40 us delay
    databits = (databits & 0x0f) | (c & 0xf0);
    LCD_STROBE;
    databits = (databits & 0x0f) | (c << 4) ;
    LCD_STROBE;
}
 
void pseudo_8bit_cmd(unsigned char c)
{
    RS(0);
    __delay_cycles(15000); //15 ms delay
    databits = (c & 0xf0);
    LCD_STROBE;
}
void clear(void)
{
    cmd(0x01);
    __delay_cycles(3000); //3 ms delay
}
 
void lcd_init()
{
    pseudo_8bit_cmd(0x30); //this command is like 8 bit mode command
    pseudo_8bit_cmd(0x30); //lcd expect 8bit mode commands at first
    pseudo_8bit_cmd(0x30); //for more details, check any 16x2 lcd spec
    pseudo_8bit_cmd(0x20);
    cmd(0x28);             //4 bit mode command started, set two line
    cmd(0x0c);             // Make cursorinvisible
    clear();               // Clear screen
    cmd(0x6);              // Set entry Mode(auto increment of cursor)
}
 
void string(char *p)
{
    while(*p) data(*p++);
}
void adc_init()
{
	ADC10CTL0 = ADC10ON | ADC10SHT_2 | SREF_0;
        ADC10CTL1 = INCH_2 | SHS_0 | ADC10DIV_0 | ADC10SSEL_0 | CONSEQ_0 ;
        ADC10AE0 = BIT2;
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

int main()
{
	int a;
       	port_init();
    	lcd_init();
	LINE1;
   	string("RESISTANCE RANGE");
	adc_init();
	while(1){
		start_conversion();
		if(!converting())

		{	
			a=ADC10MEM;
			if(a<102){
				LINE2;
				string("0k to 1k");
				delay(30000);
				}
			else if (a<204) {
				LINE2;
                                string("1k to 2k");
                                delay(30000);
				}
			else if (a<306) {
				LINE2;
                                string("2k to 3k");
                                delay(30000);
				}
			 else if (a<408) {
                                LINE2;
                                string("3k to 4k");
                                delay(30000);
                                }
			 else if (a<510) {
                                LINE2;
                                string("4k to 5k");
                                delay(30000);
                                }
			 else if (a<612) {
                                LINE2;
                                string("5k to 6k");
                                delay(30000);
                                }
			 else if (a<714) {
                                LINE2;
                                string("6k to 7k");
                                delay(30000);
                                }
			 else if (a<818) {
                                LINE2;
                                string("7k to 8k");
                                delay(30000);
                                }
			 else if (a<920) {
                                LINE2;
                                string("8k to 9k");
                                delay(30000);
                                }
			 else  {
                                LINE2;
                                string("9k to 10k");
                                delay(30000);
                                }




		}
	}
}
