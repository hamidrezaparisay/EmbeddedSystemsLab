#ifndef keypad_h
#define keypad_h


#define KEY_PORT    PORTC
#define KEY_DDR     DDRC
#define KEY_PIN     PINC

#define C1  PINC.4  
#define C2  PINC.5  
#define C3  PINC.6  
#define C4  PINC.7  



/****************functions prototypes*************************************/
void keypad_init(void);
unsigned char key_released(void);
unsigned char key_pressed(void);
unsigned char key_scan(void);

#endif