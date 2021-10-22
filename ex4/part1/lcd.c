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


int main(void)
{
  DDRD = 0xFF;
  DDRC = 0xFF;
  Lcd8_Init();
  Lcd8_Set_Cursor(1,1);
  Lcd8_Write_String("LCD Hello World");
  while(1)
  {
    
  }
}