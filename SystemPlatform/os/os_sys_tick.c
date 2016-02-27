/*
 * os_sys_tick.c
 *
 * Created: 06/09/2015 18:21:24
 *  Author: dariusz.mucha
 */ 
#include "os_sys_tick.h"
#include "libtimers.h"

static uint32_t os_sys_tick; // 1 tick = 1us

static void os_sys_tick_cnt(void)
{
	os_sys_tick++;
}

void os_sys_tick_init(void)
{
	timers_init(timer_0, os_sys_tick_cnt, timer_prescaler_64);
}

uint32_t os_get_tick(void)
{
	return os_sys_tick;
}