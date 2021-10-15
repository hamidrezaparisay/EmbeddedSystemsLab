#include <avr/io.h>
#include<avr/interrupt.h>
#define CLK 8000000L


/*
frame rate of updating 4 7segments. for a real project it should set to 
a higher number(60 or 120) but for proteus around 12 is best number 
(bcz proteus doesnt run simulation in real time)
*/
#define FPS 12 

int number = 0;
uint8_t index=0;
int timer0=0;
int timer_overflow=((CLK/1024)/(FPS*4))/256;
int timer_reminder=255-(((CLK/1024)/(FPS*4))%256);
void SevenSegment(uint8_t n)
{
	//set the 7seg
	switch (n)
	{
		case 0:
			PORTD = 0x3f;
			break;
		case 1:
			PORTD = 0x06;
			break;
		case 2:
			PORTD = 0x5b;
			break;
		case 3:
			PORTD = 0x4f;
			break;
		case 4:
			PORTD = 0x66;
			break;
		case 5:
			PORTD = 0x6d;
			break;
		case 6:
			PORTD = 0x7d;
			break;
		case 7:
			PORTD = 0x07;
			break;
		case 8:
			PORTD = 0x7f;
			break;
		case 9:
			PORTD = 0x6f;
			break;
			
	}
}
void ShowNumber(int n,uint8_t index)
{
	for(int i=0;i<index;i++)
	{
		n/=10;
	}
	SevenSegment(n%10);
	PORTC=0x0f;
	PORTC= PORTC & ~(1<<(3-index));
}
ISR (TIMER0_OVF_vect)
{
	if(timer0!=timer_overflow)
	{
		timer0++;
		return;
	}
	ShowNumber(number,index);
	if(index==3)
		index=0;
	else
		index++;
	timer0=0;
	TCNT0=timer_reminder;
}
ISR (TIMER1_OVF_vect)
{
	if(number==9999)
		number=0;
	else
		number++;
	TCNT1 = 61629;
}
int main(void)
{
	DDRC=0x0f;
	DDRD=0xff;
	
	
	TCNT0= timer_reminder;
	TCCR0 = (1<<CS02) | (1<<CS00);
	TIMSK =(1 << TOIE0) ;
	
	TCNT1 = 61629;
	TCCR1A = 0x00;
	TCCR1B = (1<<CS12) | (1<<CS10);
	TIMSK =TIMSK | (1 << TOIE1) ;
	sei();
	
	ShowNumber(1000,1);
    while(1)
    {
		
    }
}