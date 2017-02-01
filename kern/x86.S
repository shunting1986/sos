.global outl
outl:
	movw 4(%esp), %dx
	movl 8(%esp), %eax
	outl %eax, %dx
	ret

.global outw
outw:
	movw 4(%esp), %dx
	movw 8(%esp), %ax
	outw %ax, %dx
	ret

.global outb
outb:
	movw 4(%esp), %dx
	movb 8(%esp), %al
	outb %al, %dx
	ret

.global inb
inb:
	movw 4(%esp), %dx
	inb %dx, %al
	ret

.global inw
inw:
	movw 4(%esp), %dx
	inw %dx, %ax
	ret

.global inl
inl:
	movw 4(%esp), %dx
	inl %dx, %eax
	ret
