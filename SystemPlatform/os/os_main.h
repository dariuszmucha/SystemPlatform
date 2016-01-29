/*
 * os_main.h
 *
 * Created: 04/09/2015 21:39:43
 *  Author: dariusz.mucha
 */ 


#ifndef OS_MAIN_H_
#define OS_MAIN_H_

#include <stdint.h>

typedef void (*os_thread)(void);

void os_init(void);

#endif /* OS_MAIN_H_ */