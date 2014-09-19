#include <setjmp.h>

.text
.weak setjmp
.type setjmp, @function

setjmp:
.global __setjmp
.type __setjmp, @function
.align 2

__setjmp:
	# first function parameter is stored in r3
	# this is the address to a jmp_buf
	# store all registers at this location
	# except r3, because this will be passed to longjmp directly
	l.sw    ((JB_GPRS+0)*4)(r3),r1
	l.sw    ((JB_GPRS+1)*4)(r3),r2
	# not needed
	l.sw    ((JB_GPRS+3)*4)(r3),r4
	l.sw    ((JB_GPRS+4)*4)(r3),r5
	l.sw    ((JB_GPRS+5)*4)(r3),r6
	l.sw    ((JB_GPRS+6)*4)(r3),r7
	l.sw    ((JB_GPRS+7)*4)(r3),r8
	l.sw    ((JB_GPRS+8)*4)(r3),r9
	l.sw    ((JB_GPRS+9)*4)(r3),r10
	l.sw    ((JB_GPRS+10)*4)(r3),r11
	l.sw    ((JB_GPRS+11)*4)(r3),r12
	l.sw    ((JB_GPRS+12)*4)(r3),r13
	l.sw    ((JB_GPRS+13)*4)(r3),r14
	l.sw    ((JB_GPRS+14)*4)(r3),r15
	l.sw    ((JB_GPRS+15)*4)(r3),r16
	l.sw    ((JB_GPRS+16)*4)(r3),r17
	l.sw    ((JB_GPRS+17)*4)(r3),r18
	l.sw    ((JB_GPRS+18)*4)(r3),r19
	l.sw    ((JB_GPRS+19)*4)(r3),r20
	l.sw    ((JB_GPRS+20)*4)(r3),r21
	l.sw    ((JB_GPRS+21)*4)(r3),r22
	l.sw    ((JB_GPRS+22)*4)(r3),r23
	l.sw    ((JB_GPRS+23)*4)(r3),r24
	l.sw    ((JB_GPRS+24)*4)(r3),r25
	l.sw    ((JB_GPRS+25)*4)(r3),r26
	l.sw    ((JB_GPRS+26)*4)(r3),r27
	l.sw    ((JB_GPRS+27)*4)(r3),r28
	l.sw    ((JB_GPRS+28)*4)(r3),r29
	l.sw    ((JB_GPRS+29)*4)(r3),r30
	l.sw    ((JB_GPRS+30)*4)(r3),r31
	# returning from setjmp, so 0 has to be the return value
	l.addi r11,r0,0
	# hopefully r9, link register, will point to the right address
	l.jr r9
	l.nop

.text
.global longjmp
.type longjmp, @function
.align 2
longjmp:
# need to restore the registers
# r3 will point to the address where the values are stored
# r4 needs to be checked for 0 or !=0
# to return 1 or the value !=0
# return value to r11
l.addi  r13, r0, 1
l.sfeqi r4, 0x0
l.cmov  r11, r13, r4
l.lwz   r1,((JB_GPRS+0)*4)(r3)
l.lwz   r2,((JB_GPRS+1)*4)(r3)
# better not r3
l.lwz   r4,((JB_GPRS+3)*4)(r3)
l.lwz   r5,((JB_GPRS+4)*4)(r3)
l.lwz   r6,((JB_GPRS+5)*4)(r3)
l.lwz   r7,((JB_GPRS+6)*4)(r3)
l.lwz   r8,((JB_GPRS+7)*4)(r3)
l.lwz   r9,((JB_GPRS+8)*4)(r3)
l.lwz   r10,((JB_GPRS+9)*4)(r3)
# r11 already set
l.lwz   r12,((JB_GPRS+11)*4)(r3)
l.lwz   r13,((JB_GPRS+12)*4)(r3)
l.lwz   r14,((JB_GPRS+13)*4)(r3)
l.lwz   r15,((JB_GPRS+14)*4)(r3)
l.lwz   r16,((JB_GPRS+15)*4)(r3)
l.lwz   r17,((JB_GPRS+16)*4)(r3)
l.lwz   r18,((JB_GPRS+17)*4)(r3)
l.lwz   r19,((JB_GPRS+18)*4)(r3)
l.lwz   r20,((JB_GPRS+19)*4)(r3)
l.lwz   r21,((JB_GPRS+20)*4)(r3)
l.lwz   r22,((JB_GPRS+21)*4)(r3)
l.lwz   r23,((JB_GPRS+22)*4)(r3)
l.lwz   r24,((JB_GPRS+23)*4)(r3)
l.lwz   r25,((JB_GPRS+24)*4)(r3)
l.lwz   r26,((JB_GPRS+25)*4)(r3)
l.lwz   r27,((JB_GPRS+26)*4)(r3)
l.lwz   r28,((JB_GPRS+27)*4)(r3)
l.lwz   r29,((JB_GPRS+28)*4)(r3)
l.lwz   r30,((JB_GPRS+29)*4)(r3)
l.lwz   r31,((JB_GPRS+30)*4)(r3)
l.jr    r9
l.nop
