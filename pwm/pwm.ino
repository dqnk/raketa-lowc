//https://www.instructables.com/id/Arduino-Timer-Interrupts/

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 */


int time

void setup()
{

	DDRB = 0b00000001;	//	set pin 8 as output

	cli();//stop interrupts

	//set timer1 interrupt at 1Hz
	TCCR1A = 0;// set entire TCCR1A register to 0
	TCCR1B = 0;// same for TCCR1B


	//initialize counter value to 0
	TCNT1  = 0;	

	// set compare match register for 1hz increments
	// OCR1A = 16*10^6 / (frequency * prescaler) - 1 (result must be <65536)

	// 16e6/1024/1Hz - 1 
	OCR1A = 31999;  

	//	B = 16000 + param
	OCR1B = 16000 + time;

	// turn on CTC mode - timer counter resets to 0
	TCCR1B |= (1 << WGM12);

	// Set 1024 prescaler with CS12 and CS10 bits - TCCR1B = 0b00000101
	// Set 1 prescaler with just (TCCR1B = 0b00000101
	TCCR1B |= /*(1 << CS12) | */ (1 << CS10);  

	// enable timer compare interrupt for timer TCNT1
	TIMSK1 |= (1 << OCIE1B);

	//allow interrupts
	sei();
	Serial.begin(9600);
}

ISR(TIMER1_COMPB_vect)
{
	//	B interrupt
	PORTB ^= 0b00000001;
}

void loop()
{
	//do other things here
}
