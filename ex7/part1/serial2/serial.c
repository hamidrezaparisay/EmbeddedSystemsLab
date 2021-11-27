#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include<avr/interrupt.h>
#define CLK 16000000L
#define BAUD 9600
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)

unsigned int i=0;
unsigned int j=0;
void step(int t)
{
	switch(t)
	{
		case 1:
			PORTC = 0x09;
			break;
		case 2:
			PORTC = 0x0A;
			break;
		case 3:
			PORTC = 0x06;
			break;
		case 0:
			PORTC = 0x05;
			break;
	}
}

void adc_init()
{
	DDRA = 0x00;
	ADMUX = (1<<REFS0); // AREF = AVcc
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); // ADC Enable and prescaler of 128
}
uint16_t adc_read(uint8_t ch)
{
 
	ch &= 0b00000111;  // AND operation with 7
	ADMUX = (ADMUX & 0xF8)|ch;

	ADCSRA |= (1<<ADSC); // start single conversion
 
	while(ADCSRA & (1<<ADSC));// wait for conversion to complete
	return (ADC);
}
void uart_init (void)
{
    UBRRH = (BAUDRATE>>8);                      // shift the register right by 8 bits
    UBRRL = BAUDRATE;                           // set baud rate
    UCSRB|= (1<<TXEN)|(1<<RXEN) | (1 << RXCIE); // enable receiver and transmitter and enable intrupts
    UCSRC|= (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);   // 8bit data format
}
void uart_transmit (unsigned char data)
{
    while (!( UCSRA & (1<<UDRE)));                // wait while register is free
    UDR = data;                                   // load data in the register
}

unsigned char get_temp(void)
{
	uint16_t adc_result0;
	adc_result0 = adc_read(0);
	return ((uint8_t)(adc_result0/2.01)); 
}
void set_fan(void)
{
	if(j%2==0)
		TCCR0 = (1<<CS02) | (1<<CS00);//turn on the fan
	else
	{
		TCCR0 &= ~(1<<CS02);//turn off the fan
		TCCR0 &= ~(1<<CS00);
	}
	j++;
}
ISR (TIMER0_OVF_vect)
{
	TCNT0= 177;
	step(i%4);
	i++;
}
ISR(USART_RXC_vect)
{
	unsigned char a;
	a=UDR;
	if(a==1)
		uart_transmit(get_temp());
	else if(a==2)
		set_fan();
}
int main(void)
{
	DDRC=0xff;
	
	TCNT0= 177;
	TCCR0 = (1<<CS02) | (1<<CS00);//clk/1024
	TIMSK =(1 << TOIE0);
	sei();
	
	TCCR0 &= ~(1<<CS02);//disable timer
	TCCR0 &= ~(1<<CS00);
	
	adc_init();
	uart_init();
	while(1)
	{
		
    }
}