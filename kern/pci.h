#ifndef _sos_kern_pci_h
#define _sos_kern_pci_h

#define PCI_CONF_ADDR 0xCF8
#define PCI_CONF_DATA 0xCFC

#define PCI_BAR0_DWOFF 4

#define PACK_ADDR(bus, dev, func, dwoff) (0x80000000 | ((bus) << 16) | ((dev) << 11) | ((func) << 8) | ((dwoff) << 2))

typedef void pci_device_init_fn(int bus, int dev, int func);

#define DEVINFO_TO_DEVNAME(devinfo) ((devinfo) == NULL ? "unknown" : (devinfo)->device_name)

struct device_info {
	int vendor_id, device_id;
	const char *device_name;
	pci_device_init_fn *init_fn;
};

void pci_enumerate();
const char *get_vendor_name(int vendor_id);
const char *get_device_name(int vendor_id, int device_id);
struct device_info *get_device_info(int vendor_id, int device_id);

#endif
