#include <kern/seg_desc.h>
#include <inc/assert.h>

#define REMOVE_0XF(addr) ((uint32_t) (addr) & 0x0FFFFFFF)

struct seg_desc offset_seg_desc_list[] = {
	NULL_SEG_DESC(),
	SEG_DESC(0x10000000, 0xFFFFFFFF, 0xA), // code
	SEG_DESC(0x10000000, 0xFFFFFFFF, 0x2), // data
};

void
kern_init(void) {
	static_assert(sizeof(struct seg_desc) == 8);
	static_assert(sizeof(struct pseudo_desc) == 6);

	char *s = "Welcome to SOS!";
	#if 0
	char *cp = (char *) 0xB8000;
	#else
	char *cp = (char *) 0xF00B8000;
	#endif
	int i;
	for (i = 0; s[i]; i++) {
		cp[i * 2] =  s[i];
		cp[i * 2 + 1] = 3;
	}
}
