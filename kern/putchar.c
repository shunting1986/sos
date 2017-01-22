#include <kern/putchar.h>
#include <inc/stdint.h>
#include <kern/assert.h>
#include <inc/string.h>

#define CONS_WIDTH 80
#define CONS_HEIGHT 25
#define DISPLAY_MEM_BASE 0xF00B8000

#define DEF_CLR_MASK 0x0300

static unsigned int _cons_r = 0;
static unsigned int _cons_c = 0;

// NOTE: putchar does not do escape, caller should take care
void putchar(int clrch) {
	int clrmask = DEF_CLR_MASK;
	if ((clrch >> 8) == 0) {
		clrch |= clrmask;
	}
	if (_cons_r >= CONS_HEIGHT || _cons_c >= CONS_WIDTH) {
		simpanic();
	}
	switch (clrch & 0xFF) {
	case '\n':
		_cons_r++;
		_cons_c = 0;
		break;
	default:
		locputchar(_cons_r, _cons_c, clrch);
		_cons_c++;
		break;
	}
	if (_cons_c >= CONS_WIDTH) {
		_cons_r++;
		_cons_c = 0;
	}
	if (_cons_r == CONS_HEIGHT) {
		memmove((void *) DISPLAY_MEM_BASE,
			(uint16_t *) DISPLAY_MEM_BASE + CONS_WIDTH, 
			(CONS_HEIGHT - 1) * CONS_WIDTH * 2);
		int c;
		for (c = 0; c < CONS_WIDTH; c++) {
			locputchar(CONS_HEIGHT - 1, c, ' ');
		}
		_cons_r = CONS_HEIGHT - 1;
		_cons_c = 0;
	}
}

void locputchar(unsigned int r, unsigned int c, int clrch) {
	if (r >= CONS_HEIGHT || c >= CONS_WIDTH) {
		simpanic();
	}
	uint16_t *chstream = (uint16_t *) DISPLAY_MEM_BASE;
	chstream[r * CONS_WIDTH + c] = clrch;
}

void clear_screen() {
	int r, c;
	for (r = 0; r < CONS_HEIGHT; r++) {
		for (c = 0; c < CONS_WIDTH; c++) {
			locputchar(r, c, DEF_CLR_MASK | ' ');
		}
	}
}
