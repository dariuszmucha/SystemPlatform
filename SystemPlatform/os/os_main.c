/*
 * os_main.c
 *
 * Created: 04/09/2015 21:39:32
 *  Author: dariusz.mucha
 */ 

#include "os_main.h"
#include "os_defs.h"
#include "os_sys_tick.h"
#include "os_delay.h"
#include "n5110_therm_display.h"
#include "libdht11.h"

void os_init(void)
{
	os_sys_tick_init();
	n5110_therm_init();
	while(1)
	{
		dht11_update();
		n5110_therm_display_temp(dht11_get_temp());
		n5110_therm_display_humid(dht11_get_humidity());
		os_delay_ms(5);
	}
}
