#define __ASSEMBLY__
#include <l4/sys/compiler.h>

	.text

	.global _real_start
	_real_start:
/* Set stack pointer */
		l.movhi r1,hi(_stack_top)
		l.ori r1,r1,lo(_stack_top)
/* goto program start */
		l.j _start
		l.nop



	.bss
	.align 8
	_stack_bottom:
		.space 0x4000
	_stack_top:
