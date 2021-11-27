#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include<avr/interrupt.h>
#define CLK 16000000L

#define D0 eS_PORTB0
#define D1 eS_PORTB1
#define D2 eS_PORTB2
#define D3 eS_PORTB3
#define D4 eS_PORTB4
#define D5 eS_PORTB5
#define D6 eS_PORTB6
#define D7 eS_PORTB7
#define RS eS_PORTA6
#define EN eS_PORTA7

#include "lib/lcd.h"
#include "lib/keypad.h"

#define BAUD 9600                                   // define baud
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)            // set baud rate value for UBRR
  
// function to initialize UART
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

ISR(USART_RXC_vect)
{
	char buffer[10];
	unsigned char a;
	a=UDR;
	itoa(a,buffer,10);
	Lcd8_Clear();
	Lcd8_Set_Cursor(1,1);
	Lcd8_Write_String("Tempreture:");
	Lcd8_Set_Cursor(2,1);
	Lcd8_Write_String(buffer);
}

int main(void)
{
	unsigned char i;
	
	DDRB = 0xFF;
	DDRA = 0xFF;
	
	sei();
	Lcd8_Init();
	Lcd8_Set_Cursor(0,1);
	
	keypad_init();
	uart_init();
	while(1)
	{
		i = key_scan();
		if(i != 255){ 
			i=i+48;
			if(i=='1')
			{
				uart_transmit(1);
			}
			else if(i=='2')
			{
				uart_transmit(2);
			}
    }  
    }
}