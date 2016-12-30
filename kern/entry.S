#define PA(addr) (addr + 0x10000000)

.global entry_point
entry_point:
	cli

	lgdt PA(offset_gdtr_content)

	ljmp $0x08, $next
next:
	movw $0x10, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %ss
	movl $kern_stack_end, %esp

	call kern_init

1:
	jmp 1b

offset_gdtr_content:
	.word 0x17
	.long PA(offset_seg_desc_list)

# 8k kernel stack
kern_stack:
	.space 1024 * 8
kern_stack_end:

