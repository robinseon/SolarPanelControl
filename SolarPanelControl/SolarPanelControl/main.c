/*
 * 7segment.c
 *
 * Created: 01/04/2022 09:22:49
 * Author : robin
 */ 

#include <avr/io.h>
#include "Drivers/segment.h"
#include "Drivers/adc.h"
#include "Drivers/key/keydriver.h"
#include "Drivers/matrix/keyboard.h"
#include "Drivers/led/led_driver.h"
#include <avr/interrupt.h>

int main(void)
{
	init_display();
	adc_init();
	time_init();
	init_keys();
	init_keyboard();
	inits_leds();
    /* Replace with your application code */
    while (1) 
    {
    }
}

