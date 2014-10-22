
.section ".bss"
.align(0x2000)
	.global crt0_stack_low
_stack:
crt0_stack_low:
.space 8192
	.global crt0_stack_high
crt0_stack_high:


.section ".vectors", "ax"
	.global _start
	.org 0x100 /* reset */
_start:
	l.movhi r1,hi(crt0_stack_high)
	l.ori r1,r1,lo(crt0_stack_high)
	l.addi r1,r1,-4
	l.or r2,r1,r0
	l.j __main
	l.nop


/*
        .org 0x1000
.dead:
	l.nop 0x1
.deadinfinite:
	l.j .deadinfinite
	l.nop

        .org 0x2000
*/
