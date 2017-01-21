#include <kern/pci.h>
#include <kern/assert.h>
#include <inc/stdint.h>

#define PACK_ADDR(bus, dev, func, dwoff) (0x80000000 | ((bus) << 16) | ((dev) << 11) | ((func) << 8) | ((dwoff) << 2))

static void check_one_func(int bus, int dev, int func) {
	uint32_t addr = PACK_ADDR(bus, dev, func, 0);
	outl(PCI_CONF_ADDR, addr);
	uint32_t data = inl(PCI_CONF_DATA);
	if ((data & 0xffff) != 0xffff) {
		// printf("addr is %x\n", addr);
		printf("data is %x\n", data);
	}
}

void pci_enumerate() {
	int bus, dev, func;
	for (bus = 0; bus < (1 << 8); bus++) {
		for (dev = 0; dev < (1 << 5); dev++) {
			for (func = 0; func < (1 << 3); func++) {
				check_one_func(bus, dev, func);
			}
		}
	}
}
