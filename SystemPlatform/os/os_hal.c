/*
 * os_hal.c
 *
 * Created: 29/01/2016 22:23:09
 *  Author: dariusz.mucha
 */ 

#include "os_hal.h"

void os_hal_pin_direction(uint8_t port, uint8_t pin, uint8_t is_output)
{
	if(is_output)
	{
		port |= (1 << pin);
	}
	else
	{
		port &= ~(1 << pin);
	}
}

void os_hal_pin_set(uint8_t port, uint8_t pin, uint8_t val)
{
		if(val)
		{
			port |= (1 << pin);
		}
		else
		{
			port &= ~(1 << pin);
		}
}

uint8_t os_hal_pin_get(uint8_t port, uint8_t pin)
{
	return (port & (1 << pin)) != 0;	
}
