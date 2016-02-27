/*
 * libdht11.c
 *
 * Created: 2014-03-15 18:33:35
 *  Author: Dariusz
 */ 
#include <avr/io.h>
#include "libdht11.h"
#include "os_delay.h"

// Pin def
#define DHT11_DATA		PD7
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

static dht11_sensors_struc dht11_sensors;

typedef uint8_t (*condition_fun)(uint8_t, uint8_t); 

static uint8_t dht11_bit_is_set(uint8_t pin, uint8_t data)
{
	return bit_is_set(pin, data);
}

static uint8_t dht11_bit_is_clear(uint8_t pin, uint8_t data)
{
	return bit_is_clear(pin, data);
}

static uint8_t dht11_timeout(condition_fun fun)
{
	uint16_t timeout = 0;
	while(fun(DHT11_DATA_PIN, DHT11_DATA))
	{
		timeout++;
		if(timeout == 20000)
		{
			return 1;
		}
	}
	return 0;
}

static uint8_t dht11_reset(void)
{
	// data low > 13ms
	DHT11_DATA_OUT;
	DHT11_DATA_LO;	
	os_delay_us(25);
	
	// set port to input
	DHT11_DATA_HI;
	DHT11_DATA_IN;
		
	// DHT11 should drive it low soon
	if(dht11_timeout(dht11_bit_is_set)) return 0;
	if(dht11_timeout(dht11_bit_is_clear)) return 0;
	// reset complete, dht11 present
	return 1;
}

static uint8_t dht11_read(void)
{
	uint8_t data = 0;
	uint8_t i = 0, cnt = 0; 
	
	for(i = 0; i < 8; i++)
	{
		cnt = 0;
		if(dht11_timeout(dht11_bit_is_set)) return 255;
		if(dht11_timeout(dht11_bit_is_clear)) return 255;

		while(bit_is_set(DHT11_DATA_PIN, DHT11_DATA))
		{
			cnt++;
			if(cnt == 255) return 255;
		}
		if(cnt > 100)
		{
			data |= (1 << (7 - i));
		}
	}
	return data;
}

void dht11_update(void)
{
	uint8_t checksum = 0, ok = 1;
	// reset
	if(dht11_reset())
	{
		dht11_sensors.humid_h = dht11_read();
		dht11_sensors.humid_l = dht11_read();
		dht11_sensors.temp_h = dht11_read();
		dht11_sensors.temp_l = dht11_read();
		checksum = dht11_read();

		if(checksum != dht11_sensors.humid_h + dht11_sensors.humid_l + dht11_sensors.temp_h + dht11_sensors.temp_l)
		{
			ok = 0;
		}
	}
	else
	{
		ok = 0;
	}
	if(ok == 0)
	{
		dht11_sensors.humid_h = 0;
		dht11_sensors.humid_l = 0;
		dht11_sensors.temp_h = 0;
		dht11_sensors.temp_l = 0;
	}
}

uint8_t dht11_get_temp(void)
{
	return dht11_sensors.temp_h;
}

uint8_t dht11_get_humidity(void)
{
	return dht11_sensors.humid_h;
}
