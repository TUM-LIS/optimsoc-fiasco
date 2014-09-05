
.section ".bss"
.align(0x2000)
	.global crt0_stack_low
_stack:
crt0_stack_low:
.space 8192
	.global crt0_stack_high
crt0_stack_high:

	.section ".vectors"
	.global _start
	.org 0x100
_start:	
	l.j 0x2000
	l.nop

	.org 0x200
_buserror:
	l.nop
