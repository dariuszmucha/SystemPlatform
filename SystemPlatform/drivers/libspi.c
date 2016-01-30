/*
 * libspi.c
 *
 * Created: 29/01/2016 22:51:57
 *  Author: dariusz.mucha
 */ 
#include <avr/io.h>
#include "libspi.h"

void SPI_MasterInit(spi_clock_div_t clock_div, uint8_t double_speed)
{
	/* Set MOSI and SCK output, all others input */
	DDRB |= (1 << PB3) | (1 << PB5);
	/* Enable SPI, Master, set clock rate fck/64 */
	SPCR = (1<<SPE) | (1<<MSTR) | clock_div;
	if(double_speed)
	{
		SPSR |= (1 << SPI2X);
	}
}

void SPI_MasterTransmit(uint8_t cData)
{
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
}