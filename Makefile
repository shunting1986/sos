OUTROOT=obj
V=@

# extra qemu options
# EQO=-d cpu_reset -nographic

all:
	$(V)echo create sos.img with 64M size
	$(V)dd if=/dev/zero of=$(OUTROOT)/sos.img bs=1024 count=65536
	$(V)dd if=$(OUTROOT)/boot/sos_boot.bl of=$(OUTROOT)/sos.img bs=512 count=1 conv=notrunc
	$(V)dd if=$(OUTROOT)/kern/kernel of=$(OUTROOT)/sos.img bs=512 seek=1 conv=notrunc
	$(V)echo load with QEMU
	$(V)qemu-system-x86_64 -usb -hda $(OUTROOT)/sos.img $(EQO) -no-reboot -serial stdio

include boot/Makefrag
include kern/Makefrag

hello: hello_bootloader
	qemu-system-x86_64 -hda $(OUTROOT)/boot/hello.bl

clean:
	$(V)rm -rf $(OUTROOT)
