#include <avr/io.h>
#include<avr/interrupt.h>

#define F_CPU 1000000UL
#define D0 eS_PORTD0
#define D1 eS_PORTD1
#define D2 eS_PORTD2
#define D3 eS_PORTD3
#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC6
#define EN eS_PORTC7

#include "lib/lcd.h"
#include "lib/clock.h"

struct clock c;


int timer2_count=0;

ISR (TIMER2_OVF_vect)
{
	if(timer2_count!=122)//clock should do 122 overflow counts and 18 ticks.
	{
		timer2_count++;
		return;
	}
	TCNT2=256-18;
	Clock_addSecond(&c);
	timer2_count=0;
}

int main(void)
{
	DDRD = 0xFF;
	DDRC = 0xFF;
	
	TCNT2= 256-18;//clock should do 122 overflow counts and 18 ticks.
	TCCR2 = (1<<CS21) | (1<<CS20);//Clk/64
	TIMSK =(1 << TOIE2);
	sei();
	
	//init the clock
	c.sec=0;
	c.min=0;
	c.hour=0;
	
	Lcd8_Init();
	Lcd8_Set_Cursor(1,1);
	Lcd8_Write_String("00:00:00");
	while(1)
	{
    
	}
}