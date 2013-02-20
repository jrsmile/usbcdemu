/*
 * CDEMUboard.c
 *
 * Created: 1/20/2013 8:59:28 PM
 *  Author: CReno
 */ 

#include "stdio.h"
#include "CDEMUboard.h"
#include "CDEMUfatFS.h"
#include "evk1104.h"
#include "gpio.h"
#include "board.h"
#include "delay.h"
#include "navigation.h"
#include "fat.h"
#include "fs_com.h"
#include "file.h"
#include "stringz.h"
#include <string.h>


extern uint32_t ISOSizebytes;			//holder of current iso file size - size defined in CDEMUscsi.c => void d(void)
char dbgfilename_current[12];			//holder of current debug filename for debug writing routines. defined in void dbg_file_create(char *dbgfilename)

//cdemu board init
void cdemu_board_init(void)
{
	ramdrive_setup();											//format and setup of the ram drive.
	dbg_attention();											//led checker and clear...
	dbg_file_create("debug.txt");								//create debug.txt file for debug info output
}

//buttons functions//
 int buttonread(void)
{
	if(gpio_get_pin_value(GPIO_PUSH_BUTTON_SW2)) return 0;
	else return 1;
}



//project specific debug functions

void dbg_led1(uint8_t blinknum)
{
	dbg_attention();delay_ms(15);
	while(blinknum)
	{
		LED_On(LED0);		delay_ms(7);		LED_Off(LED0);		delay_ms(7);		blinknum--;
	}
while(1){}
}

void dbg_led2(uint8_t blinknum)
{
	dbg_attention();delay_ms(15);
		while(blinknum)
		{
			LED_On(LED1);			delay_ms(7);			LED_Off(LED1);			delay_ms(7);			blinknum--;
		}
	while(1){}	
}

void dbg_led3(uint8_t blinknum)
{
	dbg_attention();delay_ms(15);
	while(blinknum)
	{
		LED_On(LED2);		delay_ms(7);		LED_Off(LED2);		delay_ms(7);		blinknum--;
	}
	while(1){}
}

void dbg_led4(uint8_t blinknum)
{
	dbg_attention();delay_ms(15);
	while(blinknum)
	{
		LED_On(LED3);			delay_ms(7);			LED_Off(LED3);			delay_ms(7);			blinknum--;
	}
	while(1){}	
}

void dbg_all(uint8_t blinknum)
{
	dbg_attention();delay_ms(15);
	while(blinknum)
	{
		LED_On(LED0); LED_On(LED1); LED_On(LED2); LED_On(LED3); delay_ms(7);
		LED_Off(LED0);LED_Off(LED1);LED_Off(LED2);LED_Off(LED3);delay_ms(7);
		blinknum--;
	}
	while(1){}
}

void dbg_attention(void)
{
	uint8_t attention_time=4;
	while(attention_time)
	{
		LED_On(LED0);LED_On(LED1);LED_On(LED2);LED_On(LED3);
		delay_ms(1);
		LED_Off(LED0);LED_Off(LED1);LED_Off(LED2);LED_Off(LED3);
		delay_ms(1);
		attention_time--;
	}	
}

void dbg_attention1(void)
{
	uint8_t attention_time=4;
	while(attention_time)
	{
		LED_On(LED0);
		delay_ms(1);
		LED_Off(LED0);
		delay_ms(1);
		attention_time--;
	}
}

void dbg_attention2(void)
{
	uint8_t attention_time=4;
	while(attention_time)
	{
		LED_On(LED1);
		delay_ms(1);
		LED_Off(LED1);
		delay_ms(1);
		attention_time--;
	}
}

void dbg_attention3(void)
{
	uint8_t attention_time=4;
	while(attention_time)
	{
		LED_On(LED2);
		delay_ms(1);
		LED_Off(LED2);
		delay_ms(1);
		attention_time--;
	}
}

void dbg_attention4(void)
{
	uint8_t attention_time=4;
	while(attention_time)
	{
		LED_On(LED3);
		delay_ms(1);
		LED_Off(LED3);
		delay_ms(1);
		attention_time--;
	}
}

// debug file creation routine, call this once to setup debug file
// dbgfilename is the name of the new debug file to create
// dbgfilename is saved in a global variable for future debug calls
void dbg_file_create(char *dbgfilename)
{
		int a=0;while(a!=11){dbgfilename_current[a]=dbgfilename[a];a++;}
		nav_reset();
		nav_drive_set(nav_drive_nb() - 1);
		nav_partition_mount();					
		nav_file_create(dbgfilename_current);
		file_open(FOPEN_MODE_W_PLUS);
		file_write_buf("[-=Debug Info=-]",16);
		file_set_eof();
		file_close();
		nav_reset();
}

// Debug file write routine, DebugMessage followed by a string
void dbg_file_write(char* dbgmessage,  char* dbgwrite)
{
	fs_open();
	nav_filelist_findname( dbgfilename_current , 0 );
	if(!file_open(FOPEN_MODE_R_PLUS))dbg_led4(5);
	file_seek( 0 , FS_SEEK_END );
	file_putc(0x0d); //carriage return
	file_putc(0x0a); //line feed
	file_write_buf( dbgmessage, strlen(dbgmessage));file_putc(' ');file_putc('-');file_putc(' ');
	file_write_buf(dbgwrite, strlen(dbgwrite));
	file_set_eof();
	fs_close();
}

// Debug file write routine, DebugMessage followed by integer
void dbg_file_writeInt(char* dbgmessage, unsigned long int dbgint )
{
	char buffer[25];
	sprintf(buffer,"%d", dbgint);
	dbg_file_write(dbgmessage,buffer);
}

// Debug file write routine, DebugMessage followed by hex
void dbg_file_writeHex(char* dbgmessage, char* dbghex )
{
	char buffer[25];
	sprintf(buffer,"%#x", dbghex);
	dbg_file_write(dbgmessage,buffer);
}