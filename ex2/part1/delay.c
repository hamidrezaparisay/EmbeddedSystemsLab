#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 1000000UL
int main(void)
{
	DDRA=DDRA | ( 1<<0) ;
    while(1)
    {
		_delay_ms(500);
		PORTA=PORTA | (1<<0);
		_delay_ms(500);
		PORTA=PORTA & ~(1<<0);
    }
}