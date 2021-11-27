avr-gcc -std=c99 -O2 -Wall -mmcu=atmega32 serial.c -o serial.out
avr-objcopy -O ihex serial.out serial.hex
cmd /k