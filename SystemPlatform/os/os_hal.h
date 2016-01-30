/*
 * os_hal.h
 *
 * Created: 29/01/2016 22:22:59
 *  Author: dariusz.mucha
 */ 


#ifndef OS_HAL_H_
#define OS_HAL_H_

#include <inttypes.h>

void os_hal_pin_direction(uint8_t port, uint8_t pin, uint8_t is_output);
void os_hal_pin_set(uint8_t port, uint8_t pin, uint8_t val);
uint8_t os_hal_pin_get(uint8_t port, uint8_t pin);


#endif /* OS_HAL_H_ */