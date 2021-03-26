//https://www.instructables.com/id/Arduino-Timer-Interrupts/

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
*/

//timer1 will interrupt at 1Hz

boolean toggle1 = 0;

void setup()
{
  
	DDRB = 0b00000001;	//	set pin 8 as output

	cli();//stop interrupts

	//set timer1 interrupt at 1Hz
	TCCR1A = 0;// set entire TCCR1A register to 0
	TCCR1B = 0;// same for TCCR1B
	TCNT1  = 0;//initialize counter value to 0
	
	// set compare match register for 1hz increments
	// OCR1A = 16*10^6 / desired period - 1 (result must be <65536)
	OCR1A = 65535;  // turn on CTC mode
	TCCR1B |= (1 << WGM12);
	// Set CS12 and CS10 bits for 1024 prescaler
	TCCR1B |= (1 << CS12) | (1 << CS10);  
	// enable timer compare interrupt
	TIMSK1 |= (1 << OCIE1A);
	
	sei();//allow interrupts
	  Serial.begin(9600);
}

ISR(TIMER1_COMPA_vect)
{
	if (toggle1)
	{
		PORTB = 0b00000000;
		Serial.println("h");
	    	toggle1 = 0;
	}
	else
	{
		PORTB = 0b00000001;
	    	toggle1 = 1;
	}
}

void loop(){
  //do other things here
}
