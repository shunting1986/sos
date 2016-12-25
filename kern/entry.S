.global entry_point
entry_point:
	call kern_init
1:
	jmp 1b
