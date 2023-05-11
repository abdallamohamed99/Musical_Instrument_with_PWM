# Musical Instrument with PWM

The program continuously scans for a keypad button presses and then outputs a note using a PWM signal depending on 
what button is pressed. When a keypad button press is detected, depending on which button is pressed, the program calculates a period
for the desired output frequency. 
The calculated period is then used to calculate how many clock cycles the counter needs to count before overflowing. 
The PWM signal is then directly delivered to a headphone to output the desired tone.

## Demo
https://youtube.com/shorts/GC2yrCCgNwM?feature=share
