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
#include "n5110_therm_display.h"

void os_init(void)
{
	os_sys_tick_init();
	os_ui_init();
	n5110_therm_display_temp(24);
	n5110_therm_display_humid(51);
}
