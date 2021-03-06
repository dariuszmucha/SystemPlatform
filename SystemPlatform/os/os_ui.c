/*
 * os_debug.c
 *
 * Created: 04/09/2015 21:58:49
 *  Author: dariusz.mucha
 */ 

#include "os_ui.h"
#include "libuart.h"
#include "libn5110.h"

typedef struct {
	os_printfcn printfcn;
	os_scanfcn scanfcn;
} ui_inputs_t;

static ui_inputs_t ui_inputs;

void os_ui_init(void)
{
	N5110_Init();
	ui_inputs.printfcn = N5110_Print;
	ui_inputs.scanfcn = 0;
}

void os_print(const char* s)
{
	ui_inputs.printfcn(s);
	ui_inputs.printfcn("\n\r\0");
}

char os_scan(void)
{
	if(ui_inputs.scanfcn != 0)
	{
		return ui_inputs.scanfcn();
	}
	
	return 0;
}