/*
 * board_led_lcd.c
 *
 * Created: 1/20/2013 12:01:52 AM
 *  Author: CReno
 */ 

#include "board.h"
#include "delay.h"
#include "board_led_lcd.h"

void dbg_led1(uint8_t blinknum)
{
	dbg_attention();delay_ms(150);
	while(blinknum)
	{
		LED_On(LED0);		delay_ms(75);		LED_Off(LED0);		delay_ms(75);		blinknum--;
	}	
	while(1){}
}

void dbg_led2(uint8_t blinknum)
{
	dbg_attention();delay_ms(150);
		while(blinknum)
		{
			LED_On(LED1);			delay_ms(75);			LED_Off(LED1);			delay_ms(75);			blinknum--;
		}
	while(1){}	
}

void dbg_led3(uint8_t blinknum)
{
	dbg_attention();delay_ms(150);
	while(blinknum)
	{
		LED_On(LED2);		delay_ms(75);		LED_Off(LED2);		delay_ms(75);		blinknum--;
	}
while(1){}
}

void dbg_led4(uint8_t blinknum)
{
	dbg_attention();delay_ms(150);
		while(blinknum)
		{
			LED_On(LED3);			delay_ms(75);			LED_Off(LED3);			delay_ms(75);			blinknum--;
		}
	while(1){}	
}

void dbg_all(uint8_t blinknum)
{
	dbg_attention();delay_ms(150);
	while(blinknum)
	{
		dbg_attention();			delay_ms(75);			LED_Off(LED0);LED_Off(LED1);LED_Off(LED2);LED_Off(LED3);			delay_ms(75);			blinknum--;
	}
while(1){}
	
}
void dbg_attention(void)
{
	uint8_t attention_time=4;
	while(attention_time)
	{
		LED_On(LED0);LED_On(LED1);LED_On(LED2);LED_On(LED3);
		delay_ms(3);
		LED_Off(LED0);LED_Off(LED1);LED_Off(LED2);LED_Off(LED3);
		delay_ms(3);
		attention_time--;
	}	
}