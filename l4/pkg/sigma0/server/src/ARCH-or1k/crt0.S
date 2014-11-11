/*
* Header
*/
#define LOAD_SYMBOL_2_GPR(gpr,symbol)  \
	.global symbol ;               \
	l.movhi gpr, hi(symbol) ;      \
	l.ori   gpr, gpr, lo(symbol)

.text
		.global _start /* global should be the same as globl*/
		.type _start,%function

.global _start
_start:

/* copy from uclibc/.../or1k/crt0.S */
/* get the address of the GOT and store it in r16 */
#ifdef __PIC__
	l.jal .LPC0
#ifndef __OR1k_NODELAY__
	l.nop
#endif
.LPC0:
	LOAD_SYMBOL_2_GPR(r16, gotpchi(_GLOBAL_OFFSET_TABLE_+(.-.LPC0)))
	l.add r16, r16, r9
#endif

#ifdef __PIC__
	l.lwz r1,got(crt0_stack_high)(r16)
#else
	LOAD_SYMBOL_2_GPR(r1,crt0_stack_high)
#endif
  l.addi r1,r1,-4

	/* put the address of the _exit function into the link register */
#ifdef __PIC__
	l.lwz r9,got(_exit)(r16)
#else
	LOAD_SYMBOL_2_GPR(r9,_exit)
#endif

	/* at some point go to the init function of sigma0 */
	l.j init

.section ".bss"

	.align	8
	.global crt0_stack_low
crt0_stack_low:
	.space	2048
	.global crt0_stack_high
crt0_stack_high:
