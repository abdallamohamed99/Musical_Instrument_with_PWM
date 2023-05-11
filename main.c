/*
 * Lab5.c
 *
 * Created: 6/10/2022 6:13:26 PM
 * Author : Abdalla
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include "avr/iom328pb.h"

int const Keys [4][4] =
{
	{0,1,2,3},
	{4,5,6,7},
	{8,9,10,11},
	{12,13,14,15}
};




void scan()
{
	while(1)
	{
		for (int i=0; i<4; i++)
		{
			PORTD &= ~(1<<(PORTD4+i));	//drive low on row i
			
			for (int j = 0; j<4; j++)
			{
				if ( !(PINB & (1<<(PORTB0+j))))
				{
					Set_period(Keys[i][j]);
					
					// compare output mode = toggle OC3A
					TCCR3A |= (1<<COM3A0);					
					
					// enable the PWM on OC0A by setting the prescaler=  1
					TCCR3B |= 1<<CS30; 
					
					// Keep the PWM signal until the button is released
					while ( !(PINB & (1<<(PORTB0+j)))){};
						
					// disable to PWM signal
					TCCR3B &= ~(1<<CS30);
					
					// compare output mode = disconnect OC3A
					TCCR3A &= ~(1<<COM3A0);
					
				}
			}
			PORTD |= (1<<PORTC4+i); // drive pin high again
		}
	}
	
}

void Set_period(int key)
{
	// calculate period and 50% duty cycle
	float period = 1/(440* (pow (pow(2,((float)1/12)) , key )));
	float duty_cycle = period/2;
	
	//cycles to count
	int count = (F_CPU) * duty_cycle;
	
	// count up to the calculated value
	OCR3A = count;
	
}

int main(void)
{
	// initialize keypad IO pins
	DDRD |= 0xF0;	// rows are output and columns are inputs
	DDRB &= 0xF0;
	
	PORTD |= 0xF0;	// enable pull up resistors for the input pins and drive high for output pins
	PORTB |= 0x0F;
	
	// set OC3A as an output
	DDRD |= 1<<DDRD0;
	
	// Initialize timer
	TCCR3A |= (1<<WGM30) | (1<<WGM31);		// fast PWM mode
	TCCR3B |= (1<<WGM32) | (1<<WGM33);		// fast PWM mode

	
	while (1)
	{		
		scan();
		
	}
}