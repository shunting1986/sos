#include <kern/usb.h>
#include <kern/printf.h>
#include <kern/pci.h>
#include <kern/assert.h>

static int usb_iobase;

void usb_controller_init(int bus, int dev, int func) {
	// need bar4
	int bar4_addr = PACK_ADDR(bus, dev, func, PCI_BAR0_DWOFF + 4);
	outl(PCI_CONF_ADDR, bar4_addr);
	int bar4 = inl(PCI_CONF_DATA);
	assert(bar4 & 1); // the bar is io based rather than memory mapped
	usb_iobase = bar4 & ~1;

	// write all one bits to bar register and then read back the encoded
	// io region size
	outl(PCI_CONF_ADDR, bar4_addr);
	outl(PCI_CONF_DATA, 0xFFFFFFFF);
	outl(PCI_CONF_ADDR, bar4_addr);
	int encoded_size = inl(PCI_CONF_DATA);
	int ioreg_size = -(encoded_size & ~0xF);

	assert(ioreg_size);
	printf("usb_iobase %x size %d\n", usb_iobase, ioreg_size);
	assert((ioreg_size & (-ioreg_size)) == ioreg_size);
	assert(usb_iobase % ioreg_size == 0);
}

