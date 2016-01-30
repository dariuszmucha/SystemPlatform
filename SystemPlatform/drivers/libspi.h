/*
 * libspi.h
 *
 * Created: 29/01/2016 22:51:47
 *  Author: dariusz.mucha
 */ 
#ifndef LIBSPI_H_
#define LIBSPI_H_

#include <inttypes.h>

typedef enum {
	spi_clock_div_4 = 0,
	spi_clock_div_16 = 1,
	spi_clock_div_64 = 2,
	spi_clock_div_128 = 3
} spi_clock_div_t;

void SPI_MasterInit(spi_clock_div_t clock_div, uint8_t double_speed);
void SPI_MasterTransmit(uint8_t cData);

#endif /* LIBSPI_H_ */