#ifndef _sos_kern_pci_h
#define _sos_kern_pci_h

#define PCI_CONF_ADDR 0xCF8
#define PCI_CONF_DATA 0xCFC

void pci_enumerate();
const char *get_vendor_name(int vendor_id);
const char *get_device_name(int vendor_id, int device_id);

#endif
