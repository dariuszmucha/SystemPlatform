/*
 * libn5110.h
 *
 * Created: 29/01/2016 21:39:38
 *  Author: dariusz.mucha
 */ 

#ifndef LIBN5110_H_
#define LIBN5110_H_

#include <avr/io.h>
#include <inttypes.h>

/* 10 - sce - PB2
8 - rst - PB0
9 - d/c - PB1
*/

#define N5110_RST		PB0	
#define N5110_DC		PB1
#define N5110_SCE		PB2

#define N5110_PINS_OUT	DDRB
#define N5110_PINS_SET	PORTB

void N5110_Init(void);

void N5110_Print(const char *c);

#endif /* LIBN5110_H_ */