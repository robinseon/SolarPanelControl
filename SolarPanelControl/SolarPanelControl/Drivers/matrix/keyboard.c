/*
 * keyboard.c
 *
 * Created: 29/04/2022 11:14:02
 *  Author: robin
 */ 

#include <avr/io.h>

int c,v;//variable c to know the colon and v the value press on the keyboard
int changerow=0;//changerow is used in the function change_row to turn on and turn off the rows one by one
uint16_t bigvalue=0;//used to know the value display
int moreOneNumber=0, count=0;//used to know how many numbers are display on the 7 segments and moreOnenumber is used to do a loop just one time
int keyboard [4][4] = { //an array 2*2 like the keyboar to know which the value of the key 
	{1,2,3,10},
	{4,5,6,11},
	{7,8,9,12},
	{14,0,15,13}
};

typedef struct key_descr_t //a structur
{
	volatile uint8_t* ddr;
	volatile uint8_t* pin;
	volatile uint8_t* port;
	uint8_t bit;
} key_descr_t;

//line 1
static key_descr_t row[] = {   
	{&DDRB, &PINB, &PORTB, PB7},	// row1
	{&DDRB, &PINB, &PORTB, PB5},	// row2
	{&DDRB, &PINB, &PORTB, PB4},	// row3
	{&DDRE, &PINE, &PORTE, PE3},	// row4
};

static key_descr_t col[] = {
	{&DDRE, &PINE, &PORTE, PE5},	// col1
	{&DDRH, &PINH, &PORTH, PH3},	// col2
	{&DDRH, &PINH, &PORTH, PH5},	// col3
	{&DDRL, &PINL, &PORTL, PL1},	// col4
};

void init_keyboard()
{
	// Initialize input-pin for keys
	for(uint8_t i=0; i<4; i++)
	{
		// Initialize Data Direction Register for each row-pin
		*(row[i].ddr) |= _BV(row[i].bit);
		
		// Enable Pull-ups on each row output
		*(row[i].port) |= _BV(row[i].bit);
		
		// Initialize Data Direction Register for each col-pin
		*(col[i].ddr) &= ~_BV(col[i].bit);
		
		// Enable Pull-ups on each col input
		*(col[i].port) |= _BV(col[i].bit);
	}
}

uint8_t test_col(uint8_t key_no) //function which return 1 when the colon number key_no has a key which is pressed
{
	if((key_no >= 1) && (key_no <= 4))//to check if key_no is good
	{
		key_no--;	// Convert key number to index

		// Evaluate if key is activated (Active low)
		return ((*(col[key_no].pin) & _BV(col[key_no].bit))==0);
	}
	return 0;
}

uint8_t change_row(uint8_t nbrow)//a function to turn off or turn on the row nbrow
{
	int index=nbrow-1;
	if(changerow)//if the row is turn off, so equal to one, turn it on
	{
		*(row[index].port) |= _BV(row[index].bit);
		changerow=0;
	}
	else)//if the row is turn on, so equal to zero, turn it off
	{
		*(row[index].port) &= ~_BV(row[index].bit);
		changerow=1;
	}
}

uint8_t get_col()//function which return the number of the colon where the key is pressed
{
	for(uint8_t i=1; i<=4; i++)//check for all rows
	{
		change_row(i);//turn on a row
		for(uint8_t j=1; j<=4; j++)//check for all colons
		{
			if(test_col(j))//if a key is pressed, the test_col(j) is true
			{
				c=j;//and save the number of the colon
			}
		}
		change_row(i);//turn off the row to repeat the action with the next row
	}
	return c;//return the number of the colon
}

uint8_t get_row()//function which return the number of the row where the key is pressed
{
	int r=0;//r for the number of the row, reset each time the function is called
	for(uint8_t i=1; i<=4; i++)//check for all the rows
	{
		change_row(i);//turn on a row
		for(uint8_t j=1; j<=4; j++)//check for all colons
		{
			if(test_col(j))//if a key is pressed, the test_col(j) is true
			{
				r=i;//and save the number of the row
			}
		}
		change_row(i);//turn off the row to repeat the action with the next row
	}
	return r;//return the row
}


uint8_t getxkey()//to know the number which is pressed, with the array keyboard 2*2
{
	if (get_row()==0)//if there is not a key pressed, the value will be 99
	{
		v=99;
	}
	else//else, go take in the array the value with the row and the colon
	{
		v=keyboard[get_row()-1][get_col()-1];
	}
	return v;
}

uint16_t keyboard_display()
{
	//display all number if we press more than one number, so a big number and restart it from the beginning if you press 5 numbers
	uint16_t simpleValue=getxkey();
	if(simpleValue<=9 || simpleValue==99)//if the button *,#,A,B,C,D are pressed, nothing 
	{
		if(simpleValue==99)//if any key is pressed
		{
			moreOneNumber=0;
		}
		if (moreOneNumber==0 && simpleValue !=99)//if a key is pressed and if moreOneNummber=0, used to do the next loop just one time
		{
			if (count==4)//if there is more than 4 number, restart it
			{
				bigvalue=simpleValue;
				count=0;
			}
			else
			{
				bigvalue=bigvalue*10+simpleValue;
			}
			moreOneNumber=1;
			count++;
		}
	}
	return bigvalue;
}

void resetvalue()//used to restart the cursor
{
	bigvalue=0;
	count=0;
}