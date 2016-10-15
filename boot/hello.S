.globl entry_point
entry_point:
	.code16
	movb $'V', %al
	movb $0, %bh
	movw $5, %cx
	movb $0x0A, %ah
	int $0x10
1:
	hlt
	jmp 1b
