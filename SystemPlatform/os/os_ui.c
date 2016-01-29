/*
 * os_debug.c
 *
 * Created: 04/09/2015 21:58:49
 *  Author: dariusz.mucha
 */ 

#include "os_ui.h"
#include "libuart.h"

typedef struct {
	os_printfcn printfcn;
	os_scanfcn scanfcn;
} ui_inputs_t;

static ui_inputs_t ui_inputs;

void os_ui_init(void)
{
	USART_Init(baudrate_9600);
	ui_inputs.printfcn = USART_Transmit_String;
	ui_inputs.scanfcn = USART_Receive;
}

void os_print(const char* s)
{
	ui_inputs.printfcn(s);
	ui_inputs.printfcn("\n\r\0");
}

char os_scan(void)
{
	return ui_inputs.scanfcn();
}