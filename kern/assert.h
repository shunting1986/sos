#ifndef _sos_kern_assert_h
#define _sos_kern_assert_h

#include <kern/putchar.h>
#include <kern/printf.h>

#define assert(cond) do { \
	if (!(cond)) { \
		panic("assertion fail: " #cond); \
	} \
} while (0)

/*
 * ## before __VA_ARGS__ is the trick to support invocation like
 *    panic("hello");
 * in which case the varargs is empty.
 */
#define panic(fmt, ...) _panic(__FILE__, __LINE__, fmt, ## __VA_ARGS__)
void _panic(const char *filename, int lineno, const char *fmt, ...);

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
