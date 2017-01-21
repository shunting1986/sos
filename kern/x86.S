.global outl
outl:
	movw 4(%esp), %dx
	movl 8(%esp), %eax
	outl %eax, %dx
	ret

.global inl
inl:
	movw 4(%esp), %dx
	inl %dx, %eax
	ret
