OUTROOT=obj
V=@

all:

include boot/Makefrag

hello: hello_bootloader
	qemu-system-x86_64 -hda $(OUTROOT)/boot/hello.bl

clean:
	$(V)rm -rf $(OUTROOT)
