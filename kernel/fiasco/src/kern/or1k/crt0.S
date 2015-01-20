
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

	.org 0x100
_reset:
	// TODO: don't reset for the moment
	l.j _reset
	l.nop

	.org 0x200				/* Bus error */
_vector02:
	l.j _vector02
	l.nop

	.org 0x300 				/* Data Page Fault */
_vector03:
	l.j _vector03
	l.nop

	.org 0x400 				/* Instruction Page Fault */
_vector04:
	l.j _vector04
	l.nop

	.org 0x500 				/* Tick Timer */
_vector05:
	l.j _vector05
	l.nop

	.org 0x600 				/* Alignment */
_vector06:
	l.j _vector06
	l.nop

	.org 0x700 				/* Illegal Instruction */
_vector07:
	l.j _vector07
	l.nop

	.org 0x800 				/* External Interrupt */
_vector08:
	l.j _vector08
	l.nop

	.org 0x900 				/* D-TLB Miss */
_vector09:
	l.sw 0x4(r0),r1;
	/* Load top of the exception stack */
	l.movhi r1,hi(crt0_stack_high);
	l.ori r1,r1,lo(crt0_stack_high);
	/* Store GPR3 in context */
	l.sw -8(r1),r3;
	/* Load back software's stack pointer */
	l.lwz r3,0x4(r0);
	/* Store this in the context */
	l.sw -4(r1),r3;
	/* Store GPR4 in the context */
	l.sw -12(r1),r4;
	l.mfspr r3,r0,0x30
	l.sw -16(r1), r3
	/* Copy program counter of exception as */
	/* second argument to the exception handler */
	l.mfspr r4,r0,0x20
	l.sw -20(r1), r4
	/* Jump to exception handler. This will rfe */
	l.jal pagefault_entry
	l.addi r1,r1,-20
	l.lwz r3,0(r1)
	l.mtspr r0,r3,0x20
	l.lwz r3,4(r1)
	l.mtspr r0,r3,0x30
	l.lwz r3,12(r1)
	l.lwz r4,8(r1)
	l.lwz r1,16(r1)
	l.rfe
	l.nop

	.org 0xa00 				/* I-TLB Miss */
_vector0a:
	l.j _vector0a
	l.nop

	.org 0xb00 				/* Range */
_vector0b:
	l.j _vector0b
	l.nop

	.org 0xc00 				/* System Call */
_vector0c:
	l.j _vector0c
	l.nop

	.org 0xd00 				/* Floating Point */
_vector0d:
	l.j _vector0d
	l.nop

	.org 0xe00 				/* Trap */
_vector0e:
	l.j _vector0e
	l.nop

	.org 0x2000

