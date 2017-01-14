#include <kern/assert.h>

void _panic(const char *filename, int lineno, const char *fmt, ...) {
	printf("%s:%d:panic: ", filename, lineno);
	va_list va;
	va_start(va, fmt);
	printfmt(fmt, va, putchar);
	printf("\n");
	while (1) {
	}
}
