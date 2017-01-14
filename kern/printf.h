#ifndef _sos_kern_printf_h
#define _sos_kern_printf_h

#include <inc/stdarg.h>

typedef void putchar_fn(int);

void printf(char *fmt, ...);
void printfmt(char *fmt, va_list args, putchar_fn *);

#endif
