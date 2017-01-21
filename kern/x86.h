#ifndef _sos_kern_x86_h
#define _sos_kern_x86_h

#include <inc/stdint.h>

void outl(int port, uint32_t data);
uint32_t inl(int port);

#endif
