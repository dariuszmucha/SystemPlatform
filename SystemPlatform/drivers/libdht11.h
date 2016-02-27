/*
 * libdht11.h
 *
 * Created: 2014-03-15 18:33:44
 *  Author: Dariusz
 */ 

#ifndef _LIBDHT11_H_
#define _LIBDHT11_H_

#include <avr/io.h>
		
void dht11_update(void);
uint8_t dht11_get_temp(void);
uint8_t dht11_get_humidity(void);

#endif /* _LIBDHT11_H_ */