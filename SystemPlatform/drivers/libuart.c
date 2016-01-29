/*
 * libuart.c
 *
 * Created: 2015-01-25 21:30:05
 *  Author: dariusz.mucha
 */ 

#include "libuart.h"
#include "boarddef.h"
#include <avr/io.h>

#define BAUD 9600
#define MYUBRR ((((FOSC/16)/BAUD) -1))

void USART_Init(baudrate_t ubrr)
{
	uint8_t baud_reg;
	if(ubrr == baudrate_9600)
	{
		baud_reg = ((FOSC / 16) / 9600) - 1;
	}
	else if(ubrr == baudrate_57600)
	{
		baud_reg = ((FOSC / 16) / 57600) - 1;
	}
	else
	{
		baud_reg = ((FOSC / 16) / 9600) - 1;
	}
	/*Set baud rate */
	UBRR0H = 0;
	UBRR0L = baud_reg;
	/* Enable receiver and transmitter */
	UCSR0B = (1 << RXEN0)|(1 << TXEN0);
	/* Set frame format: 8 data, 1 stop bit */
	UCSR0C = (0 << USBS0)|(3 << UCSZ00);
}

void USART_Transmit(char data)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

void USART_Transmit_String(const char *data)
{
	uint8_t i = 0;
	while(data[i] != 0)
	{
		USART_Transmit(data[i]);
		i++;
	}
}

char USART_Receive(void)
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;
}

