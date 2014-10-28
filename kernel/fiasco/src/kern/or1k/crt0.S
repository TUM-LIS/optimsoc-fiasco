
.section ".bss"
.align(0x2000)
	.global crt0_stack_low
_stack:
crt0_stack_low:
.space 8192
	.global crt0_stack_high
crt0_stack_high:


.section ".text"
	.global _start
_start:
	l.movhi r1,hi(crt0_stack_high)
	l.ori r1,r1,lo(crt0_stack_high)
	l.addi r1,r1,-4
	l.or r2,r1,r0
	l.j bootstrap_main
	l.nop


	.section .vectors, "ax"

	.org 0x000				/* Bus error */
_vector02:
	l.ori r15,r0,0x08
	l.j _vector02
	l.nop

	.org 0x100 				/* Data Page Fault */
_vector03:
	l.ori r15,r0,0x08
	l.j _vector02
	l.nop

	.org 0x200 				/* Instruction Page Fault */
_vector04:
	l.ori r15,r0,0x08
	l.j _vector02
	l.nop

	.org 0x300 				/* Tick Timer */
_vector05:
	l.ori r15,r0,0x08
	l.j _vector02
	l.nop

	.org 0x400 				/* Alignment */
_vector06:
	l.ori r15,r0,0x08
	l.j _vector02
	l.nop

	.org 0x500 				/* Illegal Instruction */
_vector07:
	l.ori r15,r0,0x08
	l.j _vector02
	l.nop

	.org 0x600 				/* External Interrupt */
_vector08:
	l.ori r15,r0,0x08
	l.j _vector02
	l.nop

	.org 0x700 				/* D-TLB Miss */
_vector09:
	l.ori r15,r0,0x08
	l.j _vector02
	l.nop

	.org 0x800 				/* I-TLB Miss */
_vector0a:
	l.ori r15,r0,0x08
	l.j _vector02
	l.nop

	.org 0x900 				/* Range */
_vector0b:
	l.ori r15,r0,0x08
	l.j _vector02
	l.nop

	.org 0xa00 				/* System Call */
_vector0c:
	l.ori r15,r0,0x08
	l.j _vector02
	l.nop

	.org 0xb00 				/* Floating Point */
_vector0d:
	l.ori r15,r0,0x08
	l.j _vector02
	l.nop

	.org 0xc00 				/* Trap */
_vector0e:
	l.ori r15,r0,0x08
	l.j _vector02
	l.nop

	.org 0xd00 				/* Reserved ... */
_vector0f:
	l.ori r15,r0,0x08
	l.j _vector02
	l.nop

        .org 0x1000
.dead:
	l.nop 0x1
.deadinfinite:
	l.j .deadinfinite
	l.nop

        .org 0x2000
