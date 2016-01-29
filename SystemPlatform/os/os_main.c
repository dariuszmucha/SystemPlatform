/*
 * os_main.c
 *
 * Created: 04/09/2015 21:39:32
 *  Author: dariusz.mucha
 */ 

#include "os_main.h"
#include "os_defs.h"
#include "os_ui.h"
#include "os_sys_tick.h"
#include "os_delay.h"
#include "num_to_string.h"

void os_init(void)
{
	os_ui_init();
	os_sys_tick_init();
	char number[11] = {1,2,3,4,5,6,90,192,168,0,1};
	// num_to_string_hex(os_get_tick(), number);
	os_print(number);
	os_delay_us(100);	
	num_to_string_hex(os_get_tick(), number);
	os_print(number);
}