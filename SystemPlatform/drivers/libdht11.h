/*
 * libdht11.h
 *
 * Created: 2014-03-15 18:33:44
 *  Author: Dariusz
 */ 

#ifndef _LIBDHT11_H_
#define _LIBDHT11_H_

#include <avr/io.h>

#define DHT11_DATA_WAIT 60

#define LIBDHT11_DEBUG

// Pin def
#define DHT11_DATA		PD5
#define DHT11_DATA_DIR	DDRD
#define DHT11_DATA_PIN	PIND

#define DHT11_DATA_OUT	DHT11_DATA_DIR |= (1 << DHT11_DATA)
#define DHT11_DATA_IN	DHT11_DATA_DIR &= ~(1 << DHT11_DATA)

#define DHT11_DATA_ST	PORTD
#define DHT11_DATA_HI 	DHT11_DATA_ST |= (1 << DHT11_DATA)
#define DHT11_DATA_LO 	DHT11_DATA_ST &= ~(1 << DHT11_DATA)

typedef struct dht11_sensors_struc_t {
	uint8_t temp_l;
	uint8_t temp_h;
	uint8_t humid_l;
	uint8_t humid_h;
	} dht11_sensors_struc;
		
void dht11_update(void);
uint8_t dht11_get_temp(void);
uint8_t dht11_get_humidity(void);

#endif /* _LIBDHT11_H_ */