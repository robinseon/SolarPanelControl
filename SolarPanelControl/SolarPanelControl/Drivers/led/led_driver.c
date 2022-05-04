/*
 * led_driver.c
 *
 * Created: 25/02/2022 08:49:44
 *  Author: robin
 */ 

#include <avr/io.h>

void inits_leds() {
	DDRA = 0xFF;
	PORTA = 0xFF;
}

void set_led(uint8_t led_no, uint8_t state) {
	if (state == 1) {
		PORTA &= ~(1 << led_no-1);
	}
	else if (state == 0) {
		PORTA |= 1 << led_no-1;
	}
}