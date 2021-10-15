#include <avr/io.h>
#include<avr/interrupt.h>
#define F_CPU 1000000UL
#define SevenSegmentPort PORTD

uint8_t number = 0;
void SevenSegment(uint8_t n)
{
	switch (n)
	{
		case 0:
			SevenSegmentPort = 0x3f;
			break;
		case 1:
			SevenSegmentPort = 0x06;
			break;
		case 2:
			SevenSegmentPort = 0x5b;
			break;
		case 3:
			SevenSegmentPort = 0x4f;
			break;
		case 4:
			SevenSegmentPort = 0x66;
			break;
		case 5:
			SevenSegmentPort = 0x6d;
			break;
		case 6:
			SevenSegmentPort = 0x7d;
			break;
		case 7:
			SevenSegmentPort = 0x07;
			break;
		case 8:
			SevenSegmentPort = 0x7f;
			break;
		case 9:
			SevenSegmentPort = 0x6f;
			break;
			
	}
}
ISR (TIMER1_OVF_vect)
{
	if(number>=9)
		number=0;
	else
		number++;
	SevenSegment(number);
	TCNT1 = 1024;
}
int main(void)
{
	DDRC=0x01;
	DDRD=0xff;
	
	PORTC = 0x00;//for activation we should set the signal to low

	TCNT1 = 1024;
	TCCR1A = 0x00;
	//TCCR1B = (1<<CS10) | (1<<CS12);
	TCCR1B = (1<<CS11);
	TIMSK = (1 << TOIE1) ;
	sei();
	
	SevenSegment(number);
    while(1)
    {
		
    }
}