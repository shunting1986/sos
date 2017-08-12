#include <kern/usb.h>
#include <kern/printf.h>
#include <kern/pci.h>
#include <kern/assert.h>
#include <inc/stdint.h>
#include <kern/mmu.h>

static int usb_iobase;

static void check_classcode(int bus, int dev, int func) {
	outl(PCI_CONF_ADDR, PACK_ADDR(bus, dev, func, 2));
	uint32_t data = inl(PCI_CONF_DATA);
	int classcode = (data >> 24) & 0xff;
	int subcc = (data >> 16) & 0xff;
	int progif = (data >> 8) & 0xff;
	assert(classcode == 0x0C); // serial bus controller
	assert(subcc == 0x03); // usb host controller
	assert(progif == 0); // undef
}

void usb_controller_enum_fn(int bus, int dev, int func) {
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

	check_classcode(bus, dev, func);

	// Need to write back the orignally bar. Otherwise the following read/write with bar does not work
	outl(PCI_CONF_ADDR, bar4_addr);
	outl(PCI_CONF_DATA, bar4);
}

uint32_t get_frame_list_base_addr() {
	return inl(usb_iobase + USB_IO_FLBASEADD);
}

uint32_t frame_list[1024] __attribute__((aligned(4096)));

void dump_io_regs() {
	printf("Dump usb io registers\n");
	int i;
	for (i = 0; i < 16; i++) {
		int port = usb_iobase + (i << 1);
		uint16_t data = inw(port);
		printf("  data %x %x\n", port, (uint32_t) data);
	}
}

void update_run_stop_bit(int val) {
	val = val ? 1 : 0;
	uint16_t orig_val = inw(usb_iobase + USB_IO_CMD);
	outw(usb_iobase + USB_IO_CMD, (orig_val & 0xFFFFFFFE) | val);
}

void usb_init(void) {
	if (!usb_iobase) {
		panic("Fail to find usb PCI device");
	}

	dump_io_regs();
	update_run_stop_bit(0);
	outl(usb_iobase + USB_IO_FLBASEADD, PADDR(frame_list));
	outw(usb_iobase + USB_IO_FRNUM, 0);
	dump_io_regs();
	
	printf("frame list addr %x\n", frame_list);
	
	panic("ni");
}
