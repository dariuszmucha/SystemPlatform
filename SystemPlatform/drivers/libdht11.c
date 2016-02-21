/*
 * libdht11.c
 *
 * Created: 2014-03-15 18:33:35
 *  Author: Dariusz
 */ 
#include "libdht11.h"

static dht11_sensors_struc dht11_sensors;

static uint8_t dht11_reset(void)
{
	uint8_t timeout = 0;
	// data low > 13ms
	DHT11_DATA_OUT;
	DHT11_DATA_LO;	
	/*long_delay(DHT11_DATA_WAIT);*/
	
	// set port to input
	DHT11_DATA_HI;
	DHT11_DATA_IN;
		
	// DHT11 should drive it low soon
	while(bit_is_set(DHT11_DATA_PIN, DHT11_DATA))
	{
		timeout++;
		if(timeout == 255U)
		{
			return 0;
		}
	}
	timeout = 0;
	// then it should release it to high
	while(bit_is_clear(DHT11_DATA_PIN, DHT11_DATA))
	{
		timeout++;
		if(timeout == 255U)
		{
			return 0;
		}
	}
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
		while(bit_is_set(DHT11_DATA_PIN, DHT11_DATA));
		while(bit_is_clear(DHT11_DATA_PIN, DHT11_DATA));

		while(bit_is_set(DHT11_DATA_PIN, DHT11_DATA))
		{
			cnt++;
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