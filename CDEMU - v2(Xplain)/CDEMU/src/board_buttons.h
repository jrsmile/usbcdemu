/*
 * IncFile1.h
 *
 * Created: 1/19/2013 12:35:00 PM
 *  Author: CReno
 */ 


//this file will contain all button routines

#ifndef ButtonRead_H_
#define ButtonRead_H_


//reads the GP/DFU button and return 1 for pressed or 0 for released
int buttonread(void) 
{
	if(gpio_get_pin_value(GPIO_PUSH_BUTTON_SW2)) return 1;
	else return 0;
}


#endif /* ButtonRead_H_ */