#ifndef OS_DEBUG_H_
#define OS_DEBUG_H_

#ifdef UART_DEBUG

void os_debug(const char *data);
void os_debug_init(void);

#else

#define os_debug(x)
#define os_debug_init()

#endif

#endif /* OS_DEBUG_H_ */