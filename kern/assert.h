#ifndef _sos_kern_assert_h
#define _sos_kern_assert_h

#include <kern/putchar.h>

static void simpanic() {
	char *s = "...Kernel panic...";	
	int r = 0;
	int c;
	for (c = 0; s[c]; c++) {
		locputchar(r, c, (0x0400) | s[c]);
	}
	while (1) {
		// dead loop
	}
}

#endif
