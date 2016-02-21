/*
 * n5110_therm_display.h
 *
 * Created: 31/01/2016 17:39:51
 *  Author: dariusz.mucha
 */ 

#ifndef N5110_THERM_DISPLAY_H_
#define N5110_THERM_DISPLAY_H_

#include <inttypes.h>

void n5110_therm_init(void);
void n5110_therm_display_temp(uint8_t temperature);
void n5110_therm_display_humid(uint8_t humidity);

#endif /* N5110_THERM_DISPLAY_H_ */