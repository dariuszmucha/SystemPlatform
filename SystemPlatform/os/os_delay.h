/*
 * os_delay.h
 *
 * Created: 06/09/2015 18:15:45
 *  Author: dariusz.mucha
 */ 


#ifndef OS_DELAY_H_
#define OS_DELAY_H_

#include <stdint.h>

void os_delay_us(uint32_t delay);
void os_delay_ms(uint32_t delay);

#endif /* OS_DELAY_H_ */