#ifndef _sos_kern_putchar_h
#define _sos_kern_putchar_h

void locputchar(unsigned int r, unsigned int c, int clrch);

void putchar(int clrch);
void clear_screen(void);

#endif
