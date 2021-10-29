#include <avr/io.h>
#include<avr/interrupt.h>
#include <util/delay.h>
#define F_CPU 1000000UL

//RPM is 21600 so max speed of motor is when we delay 5ms between each command.
int i=0;
void step(int t)
{
	switch(t)
	{
		case 1:
			PORTA = 0x09;
			break;
		case 2:
			PORTA = 0x0A;
			break;
		case 3:
			PORTA = 0x06;
			break;
		case 0:
			PORTA = 0x05;
			break;
	}
}

int main(void)
{
	DDRA=0xff;
	DDRC=0x00;
	while(1)
	{
		if(!(PINC & (1<<2)))
		{
			step(i%4);
			i++;
			_delay_ms(5);
		}
    }
}