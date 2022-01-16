avr-gcc -std=c99 -O2 -Wall -mmcu=atmega32 lineSeeker.c -o lineSeeker.out
avr-objcopy -O ihex lineSeeker.out lineSeeker.hex
cmd /k