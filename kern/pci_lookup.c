#include <kern/pci.h>
#include <kern/assert.h>
#include <inc/stdint.h>

struct vendor_info {
	int vendor_id;
	const char *vendor_name;
};

struct vendor_info vendor_name_list[] = {
	{ 0x8086, "Intel Corporation"},
 	{ 0x1013, "Cirrus Logic"},
	{ 0xFFFF, NULL },
};

struct device_info {
	int vendor_id, device_id;
	const char *device_name;
};

struct device_info device_name_list[] = {
	{ 0x8086, 0x1237, "PCI & Memory"},
	{ 0x8086, 0x7000, "PIIX3 PCI-to-ISA Bridge (Triton II)"},
	{ 0x8086, 0x7010, "PIIX3 IDE Interface (Triton II)"},
	{ 0x8086, 0x7020, "PIIX3 USB Host Controller (Triton II)"},
	{ 0x8086, 0x7113, "PIIX4/4E/4M Power Management Controller"},
	{ 0x8086, 0x100e, "Intel Pro 1000/MT"},
	{ 0x1013, 0x00B8, "64-bit VisualMedia Accelerator"},
	{ 0xFFFF, 0xFFFF, NULL},
};

const char *get_vendor_name(int vendor_id) {
	int i;
	for (i = 0; vendor_name_list[i].vendor_id != 0xFFFF; i++) {
		if (vendor_id == vendor_name_list[i].vendor_id) {
			return vendor_name_list[i].vendor_name;
		}
	}
	return "unknown";
}

const char *get_device_name(int vendor_id, int device_id) {
	int i;
	for (i = 0; device_name_list[i].vendor_id != 0xFFFF; i++) {
		if (vendor_id == device_name_list[i].vendor_id && device_id == device_name_list[i].device_id) {
			return device_name_list[i].device_name;
		}
	}
	return "unknown";
}
