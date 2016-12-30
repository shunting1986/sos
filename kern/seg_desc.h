#ifndef _sos_kern_seg_desc_h
#define _sos_kern_seg_desc_h

#include <inc/stdint.h>

struct pseudo_desc {
	uint16_t lim;
	uint32_t base;
} __attribute__((packed));

struct seg_desc {
	uint32_t lim_low : 16;
	uint32_t base_low : 16;
	uint32_t base_mid : 8;
	uint32_t type : 4;
	uint32_t system : 1; // 0 means system segment ..
	uint32_t dpl : 2;
	uint32_t present : 1;
	uint32_t lim_high : 4;
	uint32_t avl : 1;
	uint32_t l : 1;
	uint32_t d_b : 1;
	uint32_t gran : 1;
	uint32_t base_high : 8;
};

// non-system segment descriptor
#define SEG_DESC(base, lim, type_arg) { \
	.lim_low = (((lim) >> 12) & 0xFFFF), \
	.base_low = ((base) & 0xFFFF), \
	.base_mid = (((base) >> 16) & 0xFF), \
	.type = type_arg, \
	.system = 1, \
	.dpl = 0, \
	.present = 1, \
	.lim_high = (((lim) >> 28) & 0xF), \
	.avl = 0, \
	.l = 0, \
	.d_b = 1, \
	.gran = 1, \
	.base_high = (((base) >> 24) & 0xFF), \
}

#define NULL_SEG_DESC() { \
	.lim_low = 0, \
	.base_low = 0, \
	.base_mid = 0, \
	.type = 0, \
	.system = 0, \
	.dpl = 0, \
	.present = 0, \
	.lim_high = 0, \
	.avl = 0, \
	.l = 0, \
	.d_b = 0, \
	.gran = 0, \
	.base_high = 0, \
}

#endif
