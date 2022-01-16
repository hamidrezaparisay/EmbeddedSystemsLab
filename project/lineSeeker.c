#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include<avr/interrupt.h>
#define CLK 8000000L
#define BAUD 9600
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)

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

unsigned int i=0;
unsigned int direction=0;
unsigned int state=0;
void step(int t)
{
	switch(t)
	{
		case 1:
			PORTB = 0x09;
			break;
		case 2:
			PORTB = 0x0A;
			break;
		case 3:
			PORTB = 0x06;
			break;
		case 0:
			PORTB = 0x05;
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

char get_sensor(void)
{
	char sensor=0;
	for (int i=0;i<5;i++)
	{
		if(((uint8_t)adc_read(i)) > 10)
		{
			sensor|=(1<<i);
		}
	}
	
	return sensor;
}
ISR (TIMER0_OVF_vect)
{
	TCNT0= 177;
	step(i%4);
	if(direction==0)
		i++;
	else
		i--;
}
void rotateLeft(void)
{
	direction=0;
	TCCR0 = (1<<CS02) | (1<<CS00);//turn on the rotation motor
}
void rotateRight(void)
{
	direction=1;
	TCCR0 = (1<<CS02) | (1<<CS00);//turn on the rotation motor
}
void moveForward(void)
{
	TCCR0 &= ~(1<<CS02);//turn off the rotation motor
	TCCR0 &= ~(1<<CS00);
	PORTB=0x10;
	
}
void checkSensoor(void)
{
	uint8_t sensor=(uint8_t)get_sensor();
	unsigned int last_state=state;
	if(sensor==0b00011111)
	{
		state=0;
		moveForward();
	}
	else if(sensor>=0b00010000)
	{
		state=1;
		rotateLeft();
	}
	
	else if(sensor<0b00010000)
	{
		state=2;
		rotateRight();
	}
	if(last_state!=state)
	{
		switch (state)
		{
			case 0:
				Lcd8_Clear();
				Lcd8_Write_String("Move forward");
				break;
			case 1:
				Lcd8_Clear();
				Lcd8_Write_String("Rotate left");
				break;
			default:
				Lcd8_Clear();
				Lcd8_Write_String("Rotate right");
		}
	}
}
int main(void)
{
	
	DDRD = 0xFF;
	DDRC = 0xFF;
	DDRB = 0xFF;
	
	TCNT0= 177;
	TCCR0 = (1<<CS02) | (1<<CS00);//clk/1024
	TIMSK =(1 << TOIE0);
	sei();
	
	TCCR0 &= ~(1<<CS02);
	TCCR0 &= ~(1<<CS00);
	
	
	adc_init();
	Lcd8_Init();
	Lcd8_Set_Cursor(1,1);
	
	while(1)
	{
		checkSensoor();
    }
}