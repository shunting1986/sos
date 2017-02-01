#ifndef _sos_kern_usb_h
#define _sos_kern_usb_h

void usb_controller_enum_fn(int bus, int dev, int func);
void usb_init(void);
#endif
