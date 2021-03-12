volatile int count = 0; // volatile because accessed during interrupts

void setup()
{
	cli();				  //	disable interrupts
	DDRB = 0b00000000;	  //	all inputs
	PCICR |= 0b00000001;  //	turn on interrupts for PORTB
	PCMSK0 |= 0b00000001; //	turn on interrupts for specific pin (B8)
	sei();				  //	enable interrupts again
	Serial.begin(9600);
}

void loop()
{
}

ISR(PCINT0_vect) // ISR for PORTB
{
	if (!(PINB & 1)) //	falling edge on B8
	{
		count++; //	count the interrupt
		Serial.println(count);
	}
}
