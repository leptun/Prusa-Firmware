//uart2.h
#ifndef _UART2_H
#define _UART2_H

#include <inttypes.h>
#include <stdio.h>


#if defined(__cplusplus)
extern "C" {
#endif //defined(__cplusplus)


extern FILE _uart2io;
#define uart2io (&_uart2io)


extern void uart2_init(void);

extern int8_t uart2_rx_str_P(const char* str);

extern int uart2_putchar(char c, __attribute__((unused)) FILE *stream);

extern int uart2_getchar(__attribute__((unused)) FILE *stream);


#if defined(__cplusplus)
}
#endif //defined(__cplusplus)
#endif //_UART2_H
