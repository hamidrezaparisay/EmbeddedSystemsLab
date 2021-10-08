#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 1000000UL
int main(void)
{
	DDRB=0xff;
	DDRA = DDRA & ~(1<<0);
	
    while(1)
    {
		if(PINA & (1<<0))
		{
			_delay_ms(500);
			if(PINA & (1<<0))//check if button is still pushed after delay
				PORTB = 0xff;
			_delay_ms(500);
			if(PINA & (1<<0))//check if button is still pushed after delay
				PORTB = 0x00;
		}
		else
		{
			PORTB = 0x00;
		}
    }
}