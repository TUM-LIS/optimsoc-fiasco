IMPLEMENTATION [or1k]:

#include <panic.h>

inline
bool
cas_unsafe( Mword *ptr, Mword oldval, Mword newval )
{
	Mword ret;
  asm volatile (
		"	1: l.lwa r11,0(%1)	\n\t"
		"	l.sfeq r11,%2								\n\t"
		"	l.bnf 2							\n\t"
		"	l.swa 0(%1),%3							\n\t"
		"	l.bnf 1							\n\t"
		"	2: l.nop							\n\t"
		: "=r" (ret) 
		: "r" (ptr), "r" (oldval), "r" (newval)
		: );

	return ret;
}

/* dummy implement */
bool
cas2_unsafe( Mword *, Mword *, Mword *)
{
	panic("%s not implemented", __func__);
  return false;
}

inline
void
atomic_and (Mword *l, Mword mask)
{
  Mword old;
  do { old = *l; }
  while ( !cas (l, old, old & mask));
}

inline
void
atomic_or (Mword *l, Mword bits)
{
  Mword old;
  do { old = *l; }
  while ( !cas (l, old, old | bits));
}
