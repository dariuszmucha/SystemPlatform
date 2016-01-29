/*
 * os_delay.c
 *
 * Created: 06/09/2015 18:15:36
 *  Author: dariusz.mucha
 */ 

#include "os_delay.h"
#include "os_sys_tick.h"

void os_delay_us(uint32_t delay)
{
	uint32_t tick = os_get_tick();
	while(tick + delay > os_get_tick());
}

void os_delay_ms(uint32_t delay)
{
	uint32_t tick = os_get_tick();
	uint32_t delay_tick = delay * 1000UL;
	while(tick + delay_tick > os_get_tick());
}