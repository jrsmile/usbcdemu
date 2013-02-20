/*
 * IncFile1.h
 *
 * Created: 1/19/2013 12:35:00 PM
 *  Author: CReno
 */ 


//this file will contain all button routines

#ifndef CDEMUboard_H_
#define CDEMUboard_H_

#include "stdio.h"

//cdemu board init
void cdemu_board_init(void);

/**********************
 Button interface   
**********************/

//reads the GP/DFU button and return 1 for pressed or 0 for released
int buttonread(void);

/************************
 LCD interface
************************/

//future when lcd get added to project



/************************
 LED interface
************************/

// basic on and of are already defined by default: led_On(LED#) led_Off(LED#) # = 0 - 3 
// future functions will go here.


/*************************
 Debug routines        
*************************/

// dbg_led1-4 are debug test routines you can use in code to help trouble shoot.
// ex. dbg_led1(5) - will trigger the debug attention leds, then blink led1 5 times.
// after dbg routine is finished the board goes into a loop until reset.
void dbg_led1(unsigned char);		//trigger led 1
void dbg_led2(unsigned char);		//trigger led 2
void dbg_led3(unsigned char);		//trigger led 3
void dbg_led4(unsigned char);		//trigger led 4
void dbg_all(unsigned char);		// trigger all leds

// these routines are used before a debug led message. cleares the leds on board and flashes an attention
void dbg_attention(void);
//this routine is just an attention on the leds0-3
void dbg_attention1(void);
void dbg_attention2(void);
void dbg_attention3(void);
void dbg_attention4(void);

//debug file routines.
void dbg_file_create(char *dbgfilename);
void dbg_file_write(char * dbgmsessage, char * dbgwrite);
void dbg_file_writeInt(char* dbgmessage, unsigned long int dbgint );
void dbg_file_writeHex(char* dbgmessage, char* dbghex );


#endif /* CDEMUboard_H_ */