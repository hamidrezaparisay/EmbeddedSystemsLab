avr-gcc -std=c99 -O2 -Wall -mmcu=atmega32 timer.c -o timer.out
avr-objcopy -O ihex timer.out .timer.hex
cmd /k