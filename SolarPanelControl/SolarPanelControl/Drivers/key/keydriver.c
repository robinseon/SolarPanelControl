/*
 * key_driver.c
 *
 * Created: 25/02/2022 11:24:20
 *  Author: robin
 */ 

#include <avr/io.h>

void init_keys()
{
	//Set DDRC on input
	DDRC &= ~(_BV(PINC0) | _BV(PINC1) | _BV(PINC2) | _BV(PINC3) | _BV(PINC4) | _BV(PINC5));
	// Set PORTC 0-5 to pull up on input
	PORTC |= _BV(PINC0) | _BV(PINC1) | _BV(PINC2) | _BV(PINC3) | _BV(PINC4) | _BV(PINC5);
}

uint8_t get_key(uint8_t key_no)// key_no [1..6], return true if key pressed
{
	uint8_t statut = PINC & _BV(key_no - 1);//read port C pin key_no-1
	if (statut == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}