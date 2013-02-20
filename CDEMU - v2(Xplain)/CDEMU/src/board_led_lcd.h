/*
 * board_led_lcd.h
 *
 * Created: 1/19/2013 11:58:57 PM
 *  Author: CReno
 */ 


#ifndef BOARD_LED_LCD_H_
#define BOARD_LED_LCD_H_

// dbg_led1-4 are debug test routines you can use in code to help trouble shoot.
// ex. dbg_led1(5) - will trigger the debug attention leds, then blink led1 5 times. 
// after dbg routine is finished the board goes into a loop until reset.
void dbg_led1(uint8_t);		//trigger led 1
void dbg_led2(uint8_t);		//trigger led 2
void dbg_led3(uint8_t);		//trigger led 3
void dbg_led4(uint8_t);		//trigger led 4
void dbg_all(uint8_t);		// trigger all leds

// this routine is used before a debug led message. cleares the leds on board and flashes an attention
void dbg_attention(void);


#endif /* BOARD_LED_LCD_H_ */