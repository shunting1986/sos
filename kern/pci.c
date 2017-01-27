#include <kern/pci.h>
#include <kern/assert.h>
#include <inc/stdint.h>

#define PCI_DEBUG 0

static void check_one_func(int bus, int dev, int func) {
	uint32_t addr = PACK_ADDR(bus, dev, func, 0);
	outl(PCI_CONF_ADDR, addr);
	uint32_t data = inl(PCI_CONF_DATA);
	if ((data & 0xffff) != 0xffff) {
		int vendor_id = data & 0xffff;
		int device_id = (data >> 16) & 0xffff;
		struct device_info *devinfo = get_device_info(vendor_id, device_id);

		#if PCI_DEBUG
		printf("- %d:%d:%d %x (%s) %x (%s)\n", bus, dev, func,
			vendor_id,
			get_vendor_name(vendor_id),
			device_id,
			DEVINFO_TO_DEVNAME(devinfo));
		int addr_ind;
		for (addr_ind = 0; addr_ind < 6; addr_ind++) {
			outl(PCI_CONF_ADDR, PACK_ADDR(bus, dev, func, PCI_BAR0_DWOFF + addr_ind));
			uint32_t bar = inl(PCI_CONF_DATA);
			printf("    bar %d %x\n", addr_ind, bar);
		}
		#endif

		if (devinfo && devinfo->init_fn) {
			devinfo->init_fn(bus, dev, func);
		}
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
