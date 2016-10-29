.globl entry_point
entry_point:
	.code16
	cli

	# SAMPLE: print 2 X with bios
 	# movb $'X', %al
 	# movb $0, %bh
 	# movw $2, %cx
 	# movb $0x0A, %ah
 	# int $0x10

	# load 512K from sector 1 to 0x10000
	# XXX only load 127 sectors for now due to BISO interface restriction
	# XXX need a loop
	# NOTE: chs, c from 0, h from 0, s from 1
	movw $0x027F, %ax
	movw $0x0002, %cx
	movw $0x0080, %dx # lower byte specifies the drive
	movw $0x1000, %bx # can not move imm to cr directly, so use 2 insns
	movw %bx, %es
	xorw %bx, %bx
	int $0x13

	# SAMPLE: override segreg to print the first 2 characters
  # movb %es:1, %al
  # movb $0, %bh
  # movw $2, %cx
  # movb $0x0A, %ah
  # int $0x10
 
  # movb %es:0, %al
  # movb $0, %bh
  # movw $1, %cx
  # movb $0x0A, %ah
  # int $0x10

	# jmp to protected mode and then load the elf file
	movl %cr0, %eax # access eax even in real address mode
	orl $1, %eax
	movl %eax, %cr0

	lgdt prot_gdt_pseudo
	ljmp $0x08, $next
	.code32
next:
	# SAMPLE: print the first several characters of kernel
	movb 0x10000, %al
	movb %al, 0xB8000
	movb $0x03, 0xB8001
	movb 0x10001, %al
	movb %al, 0xB8002
	movb $0x03, 0xB8003
	movb 0x10002, %al
	movb %al, 0xB8004
	movb $0x03, 0xB8005
1:
	jmp 1b
prot_gdt_table:
	# null segment descriptor
	.long 0
	.long 0
	# code segment descriptor
	.long 0x0000FFFF
	.long 0x00CF9A00
	# data segment descriptor
	.long 0x0000FFFF
	.long 0x00CF9200

prot_gdt_pseudo:
	.word 0x17
	.long prot_gdt_table
