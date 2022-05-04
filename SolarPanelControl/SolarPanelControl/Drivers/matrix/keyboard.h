/*
 * keyboard.h
 *
 * Created: 29/04/2022 11:14:17
 *  Author: robin
 */ 


#ifndef KEYBOARD_H_
#define KEYBOARD_H_


void init_keyboard();
uint8_t getxkey();
uint8_t get_row();
uint16_t keyboard_display();
void resetvalue();


#endif /* KEYBOARD_H_ */