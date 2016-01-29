/*
 * libn5110.h
 *
 * Created: 29/01/2016 21:39:38
 *  Author: dariusz.mucha
 */ 

#ifndef LIBN5110_H_
#define LIBN5110_H_

/* 10 - sce - PB2
8 - rst - PB0
9 - d/c - PB1
*/

#define N5110_RST		PB0	
#define N5110_DC		PB1

#define N5110_PINS_OUT	DDRB
#define N5110_PINS_SET	PORTB

//E cycle musi trwac min 1400ns
#define EN_SBI 	EN_SET |= (1 << EN); short_delay(1);
#define EN_CLR 	EN_SET &= ~(1 << EN); short_delay(1);
#define PULSE	EN_SBI EN_CLR

void N5110_Init(void);

void N5110_Print(char *c);

#endif /* LIBN5110_H_ */