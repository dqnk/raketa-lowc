/*	This is just for debugging, testing and understanding arduino and its components 
*/
#include <avr/interrupt.h>

volatile int z = 0;
volatile int x = 0;
volatile int y = 999;

void setup()
{
	cli();				  //	disable interrupts
	DDRB = 0b00000000;	  // 	all digital pins B are inputs
	DDRD = 0b00000000;	  //	pin 3 is input
	PCICR |= 0b00000100;  //	turn on interrupts for PORTD
	PCMSK2 |= 0b00001000; //	turn on interrupts for specific pin (pin 3)
	DDRB = 0b00001000;	  //	pin 11 is output

	sei(); //	enable interrupts
	Serial.begin(9600);
}

void loop()
{
	print();
	delay(1000);
	PORTB = 0b00001000; //	pin 11 set to high
	print();
	delay(1000);
	PORTB = 0b00000000; //	pin 11 set to low
}

inline void print()
{
	Serial.print("x: ");
	Serial.println(x);
	Serial.print("y: ");
	Serial.println(y);
	Serial.print("z: ");
	Serial.println(z);
	Serial.println();
}

ISR(PCINT2_vect) //	Port D, PCINT16 - PCINT23
{
	x++;
	if (!(PIND & (1 << 3))) //	only falling edge
	{
		z++;
	}
	if (PIND & (1 << 3)) //	only rising edge
	{
		y--;
	}
}
