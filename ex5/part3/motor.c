#include <avr/io.h>
#include<avr/interrupt.h>
#define CLK 1000000L

#define START_TIMER0 TCCR0 |= (1<<CS0)|(1<<CS2)
#define STOP_TIMER0  TCCR0B &= 0B11111000

//RPM is 21600 so max speed of motor is when we delay 5ms between each command.
unsigned int i=0;
uint8_t control=1;
uint8_t enable=1;
uint8_t phase=0;
float time=40.96;

int timer0_count=0;

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
int timeToOffset()
{
	return (int)((CLK/1024)*(time/1000));
}
ISR (TIMER0_OVF_vect)
{
	if(phase%4==0 || phase%4==2)
	{
		if(time>5.12)
			time-=1;//decreasing time between each command;
		else
			time=5.12;
	}
	else
	{
		if(time<40.96)
			time+=1;//increasing time between each command;
		else
			time=40.96;
	}
	TCNT0=256-timeToOffset();
	
	step(i%4);
	if (phase%4==0 || phase%4==1)
		i++;
	else
		i--;
	
	if(timer0_count!=150)
	{
		timer0_count++;
	}
	else
	{
		phase++;
		timer0_count=0;
	}
	
}
int main(void)
{
	DDRA=0xff;
	DDRC=0x00;
	
	TCNT0= 256-timeToOffset();//every clk/8 cycles we should decrease delay
	TCCR0 = (1<<CS02) | (1<<CS00);//clk/1024
	TIMSK =(1 << TOIE0);
	sei();
	
	
	
	while(1)
	{
		if(!(PINC & (1<<2)))
		{
			if(control==1)
			{
				enable++;
				if(enable%2==0)
				{
					TCNT0= 256-timeToOffset();
					TCCR0 = (1<<CS02) | (1<<CS00);//clk/1024
				}
				else
				{
					TCCR0 &= ~(1<<CS02);//disable timer
					TCCR0 &= ~(1<<CS00);//clk/1024
					time=40.96;
					phase=0;
					timer0_count=0;
				}
				control=0;
			}
		}
		else{
			control=1;
		}
    }
}