#ifndef _sos_kern_x86_h
#define _sos_kern_x86_h

#include <inc/stdint.h>

void outb(int port, uint8_t data);
void outw(int port, uint16_t data);
void outl(int port, uint32_t data);
uint8_t inb(int port);
uint16_t inw(int port);
uint32_t inl(int port);

#endif
