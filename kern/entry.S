.global entry_point
entry_point:
	cli
	movl $kern_init, %eax
	andl $0x0FFFFFFF, %eax
	call *%eax
1:
	jmp 1b
