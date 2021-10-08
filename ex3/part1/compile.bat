avr-gcc -O2 -Wall -mmcu=atmega32 delay.c -o delay.out
avr-objcopy -O ihex delay.out .delay.hex