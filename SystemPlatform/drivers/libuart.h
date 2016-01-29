/*
 * libuart.h
 *
 * Created: 2015-01-25 21:29:49
 *  Author: dariusz.mucha
 */ 
#ifndef LIBUART_H_
#define LIBUART_H_

#include <avr/io.h>

typedef enum baudrate_t {
	baudrate_9600,
	baudrate_57600
} baudrate_t;

void USART_Init(baudrate_t ubrr);

void USART_Transmit( char data );
void USART_Transmit_String(const char *data);

char USART_Receive( void );


#endif /* LIBUART_H_ */