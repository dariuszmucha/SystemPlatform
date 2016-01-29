/*
 * debug.h
 *
 * Created: 04/09/2015 21:42:40
 *  Author: dariusz.mucha
 */ 


#ifndef DEBUG_H_
#define DEBUG_H_

typedef void (*os_printfcn)(const char*);
typedef char (*os_scanfcn)(void);

void os_ui_init(void);
void os_print(const char*);
char os_scan(void);

#endif /* DEBUG_H_ */