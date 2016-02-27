#include "libuart.h"

#ifdef UART_DEBUG

void os_debug(const char* debug_str)
{
	USART_Transmit_String(debug_str);
}

void os_debug_init(void)
{
	USART_Init(baudrate_9600);
}

#endif
