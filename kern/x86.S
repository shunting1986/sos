.global outl
outl:
	movw 4(%esp), %dx
	movl 8(%esp), %eax
	outl %eax, %dx
	ret

.global outb
outb:
	movw 4(%esp), %dx
	movb 8(%esp), %al
	outb %al, %dx
	ret

.global inl
inl:
	movw 4(%esp), %dx
	inl %dx, %eax
	ret
