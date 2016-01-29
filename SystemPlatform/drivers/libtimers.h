/*
 * libtimers.h
 *
 * Created: 04/09/2015 22:26:18
 *  Author: dariusz.mucha
 */ 


#ifndef LIBTIMERS_H_
#define LIBTIMERS_H_

typedef enum {
	timer_0,
	timer_1,
	timer_2
} timer_t;

typedef enum {
	timer_prescaler_no		= 1,
	timer_prescaler_8		= 2,
	timer_prescaler_64		= 3,
	timer_prescaler_256		= 4,
	timer_prescaler_1024	= 5
} timer_prescaler_t;

typedef void (*timer_callback)(void);

void timers_init(timer_t timer, timer_callback f, timer_prescaler_t prescaler);



#endif /* LIBTIMERS_H_ */