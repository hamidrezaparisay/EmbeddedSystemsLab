avr-gcc -std=c99 -O2 -Wall -mmcu=atmega32 lcd.c -o lcd.out
avr-objcopy -O ihex lcd.out .lcd.hex
cmd /k