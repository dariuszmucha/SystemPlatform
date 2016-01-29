/*
 * libtimers.c
 *
 * Created: 04/09/2015 22:26:30
 *  Author: dariusz.mucha
 */ 

#include "libtimers.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stddef.h>

static timer_callback timer_callbacks[3];

ISR(TIMER0_COMPA_vect)
{
	TCNT0 = 0;
	if(timer_callbacks[timer_0] != NULL) timer_callbacks[timer_0]();
}
ISR(TIMER1_OVF_vect)
{
	if(timer_callbacks[timer_1] != NULL) timer_callbacks[timer_1]();
}
ISR(TIMER2_OVF_vect)
{
	if(timer_callbacks[timer_2] != NULL) timer_callbacks[timer_2]();
}

static void timer_0_init(timer_prescaler_t prescaler)
{
	TCCR0B |= prescaler;
	OCR0A = 16;
	TIMSK0 |= (1 << OCIE0A);
	TCNT0 = 0;
}

static void timer_1_init(timer_prescaler_t prescaler)
{
	TCCR1B |= prescaler;
	TIMSK1 |= (1 << TOIE1);
	TCNT1 = 0;
}

static void timer_2_init(timer_prescaler_t prescaler)
{
	TCCR2B |= prescaler;
	TIMSK2 |= (1 << TOIE2);
	TCNT2 = 0;
}

void timers_init(timer_t timer, timer_callback f, timer_prescaler_t prescaler)
{
	sei();
	switch(timer)
	{
		case timer_0:
			timer_0_init(prescaler);
			timer_callbacks[timer_0] = f;
			break;
		case timer_1:
			timer_1_init(prescaler);
			timer_callbacks[timer_1] = f;
			break;
		case timer_2:
			timer_2_init(prescaler);
			timer_callbacks[timer_2] = f;
			break;
	}
}