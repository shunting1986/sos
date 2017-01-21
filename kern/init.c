#include <kern/seg_desc.h>
#include <inc/assert.h>
#include <kern/putchar.h>
#include <kern/assert.h>
#include <kern/printf.h>
#include <kern/pci.h>

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
	printf("Welcome to SOS %d\nHave fun\n", 2017);
	pci_enumerate();
	panic("%s!", "not ready yet");
}
