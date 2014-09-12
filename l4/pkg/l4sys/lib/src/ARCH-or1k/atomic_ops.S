.globl l4_atomic_add
l4_atomic_add:
	l.sys 0x0815

.globl l4_atomic_cmpxchg
l4_atomic_cmpxchg:
	l.sys 0x0815

.globl l4_atomic_xchg
l4_atomic_xchg:
	l.sys 0x0815

