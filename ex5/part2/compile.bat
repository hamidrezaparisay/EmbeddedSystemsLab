avr-gcc -std=c99 -O2 -Wall -mmcu=atmega32 motor.c -o motor.out
avr-objcopy -O ihex motor.out .motor.hex
cmd /k