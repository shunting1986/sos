#ifndef _sos_kern_usb_h
#define _sos_kern_usb_h

#define USB_IO_CMD 0x00
#define USB_IO_FRNUM 0x06
#define USB_IO_FLBASEADD 0x08

void usb_controller_enum_fn(int bus, int dev, int func);
void usb_init(void);
#endif
