/*
 * os_sys_tick.h
 *
 * Created: 06/09/2015 18:20:35
 *  Author: dariusz.mucha
 */ 


#ifndef OS_SYS_TICK_H_
#define OS_SYS_TICK_H_

#include <stdint.h>

void os_sys_tick_init(void);
uint32_t os_get_tick(void);

#endif /* OS_SYS_TICK_H_ */