INTERFACE[or1k]:

#include "entry_frame.h"
#include "member_offs.h"
#include "types.h"

class Continuation
{
  MEMBER_OFFSET();

private:
  Address _ip;
  Mword   _psr;

public:
  Continuation() : _ip(~0UL) {}

  struct User_return_frame
  {
    Mword usp;
    Mword ulr;
    Mword km_lr;
    Mword psr;
    Mword pc;
  };

  bool valid() const
  { return _ip != ~0UL; }

  Address ip() const { }
  void ip(Address ip) { }

  Mword flags(Return_frame const *) const {  }
  void flags(Return_frame *, Mword psr) {  }

  Mword sp(Return_frame const *o) const {  }
  void sp(Return_frame *o, Mword sp) { }

  void save(Return_frame const *regs)
  {
  }

  void activate(Return_frame *regs, void *cont_func)
  {
  }

  void set(Return_frame *dst, User_return_frame const *src)
  {
  }

  void get(User_return_frame *dst, Return_frame const *src) const
  {

  }

  void clear() { _ip = ~0UL; }

  void restore(Return_frame *regs)
  {
  }

};

