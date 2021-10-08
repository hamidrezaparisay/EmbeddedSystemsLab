#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 1000000UL
void turnOn(int index)
{
	PORTB= PORTB | (1<<index);
	_delay_ms(500);
	PORTB= PORTB & ~(1<<index);
}
int main(void)
{
	DDRB=0xff;
	DDRA = DDRA & ~(1<<0);
	
    while(1)
    {
		if(PINA & (1<<0))
		{
			for (int i=0;i<8;i++)
			{
				turnOn(i);
			}
		}
		else
		{
			PORTB = 0x00;
		}
    }
}