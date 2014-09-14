IMPLEMENTATION [or1k]:

#include <panic.h>

inline
bool
cas_unsafe( Mword *ptr, Mword oldval, Mword newval )
{
  asm volatile ("l.sys 0x0815");
	//panic("%s not implemented", __func__);
	return false;
}

/* dummy implement */
bool
cas2_unsafe( Mword *, Mword *, Mword *)
{
  asm volatile ("l.sys 0x0815");
	//panic("%s not implemented", __func__);
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
