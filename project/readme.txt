This project present a 3 state line seeker.

There are 5 buttons that act like pixel sensors.avr reads them through adc (offcourse we dont need to read button state through adc, but in reality when we use real pixel sensors we should use adc) and make decision based on 3 state:
-move forward
-rotating right
-rotating left

There is a lcd that show the desicion avr making.