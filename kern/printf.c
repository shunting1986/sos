#include <kern/printf.h>
#include <kern/assert.h>
#include <kern/putchar.h>

void printf(char *fmt, ...) {
	va_list va;
	va_start(va, fmt);
	printfmt(fmt, va, putchar);
}

void printnum_rec(unsigned int num, putchar_fn *putchar) {
	unsigned rem = num % 10;
	num /= 10;
	if (num) {
		printnum_rec(num, putchar);
	}
	putchar(rem + '0');
}

static void printnum(int num, putchar_fn *putchar) {
	if (num < 0) {
		putchar('-');
		num = -num;
	}
	if (num == 0) {
		putchar('0');
		return;
	}
	printnum_rec(num, putchar);
}

void printfmt(char *fmt, va_list args, putchar_fn *putchar) {
	int i;
	for (i = 0; fmt[i]; i++) {
		char ch = fmt[i];
		// handle %d TODO have a general solution for all escapes
		if (fmt[i] == '%' && fmt[i + 1] == 'd') {
			printnum(va_arg(args, int), putchar);
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
