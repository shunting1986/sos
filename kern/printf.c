#include <kern/printf.h>
#include <kern/assert.h>
#include <kern/putchar.h>
#include <inc/stdint.h>
#include <kern/assert.h>

void printf(char *fmt, ...) {
	va_list va;
	va_start(va, fmt);
	printfmt(fmt, va, putchar);
}

void printnum_rec(unsigned long long num, int base, putchar_fn *putchar) {
	assert(base >= 2 && base <= 16);
	unsigned rem = num % base;
	num /= base;
	if (num) {
		printnum_rec(num, base, putchar);
	}
	putchar("0123456789abcdef"[rem]);
}

static void printnum(long long num, int base, putchar_fn *putchar) {
	if (num < 0) {
		putchar('-');
		num = -num;
	}
	if (num == 0) {
		putchar('0');
		return;
	}
	printnum_rec(num, base, putchar);
}

void printfmt(char *fmt, va_list args, putchar_fn *putchar) {
	int i;
	for (i = 0; fmt[i]; i++) {
		char ch = fmt[i];
		// handle %d TODO have a general solution for all escapes
		if (fmt[i] == '%' && fmt[i + 1] == 'd') {
			printnum(va_arg(args, int), 10, putchar);
			i++;
		} else if (fmt[i] == '%' && fmt[i + 1] == 'x') {
			printnum(va_arg(args, uint32_t), 16, putchar);
			i++;
		} else if (fmt[i] == '%' && fmt[i + 1] == 's') {
			char *s = va_arg(args, char *);
			while (*s) {
				putchar(*s++);
			}
			i++;
		} else {
			putchar(ch);
		}
	}
}
