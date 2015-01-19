INTERFACE[or1k]:

#include "types.h"

EXTENSION class Syscall_frame
{
  public:
    Mword r[30]; //{r0, r2, r3, ..., r10, r13 .., r31, ip
    void dump() const;
};

EXTENSION class Return_frame
{
  public:
    void dump();
    void dump_scratch();
    bool user_mode();
};

//------------------------------------------------------------------------------
IMPLEMENTATION [or1k]:

#include "warn.h"
/*#include "psr.h" */

IMPLEMENT
void
Syscall_frame::dump() const
{
}

IMPLEMENT
void
Return_frame::dump()
{

}

IMPLEMENT
void
Return_frame::dump_scratch()
{
}

IMPLEMENT inline
Mword
Return_frame::sp() const
{

}

IMPLEMENT inline
void
Return_frame::sp(Mword _sp)
{

}

IMPLEMENT inline
Mword
Return_frame::ip() const
{

}

IMPLEMENT inline
void
Return_frame::ip(Mword _pc)
{

}

IMPLEMENT inline //NEEDS ["psr.h"]
bool
Return_frame::user_mode()
{
  return 0;
  /*return Msr::Msr_pr & srr1;*/
}

//---------------------------------------------------------------------------
//TODO cbass: set registers properly 
IMPLEMENT inline
Mword Syscall_frame::next_period() const
{ return false; }

IMPLEMENT inline
void Syscall_frame::from(Mword id)
{  }

IMPLEMENT inline
Mword Syscall_frame::from_spec() const
{  }


IMPLEMENT inline
L4_obj_ref Syscall_frame::ref() const
{  }

IMPLEMENT inline
void Syscall_frame::ref(L4_obj_ref const &ref)
{  }

IMPLEMENT inline
L4_timeout_pair Syscall_frame::timeout() const
{  }

IMPLEMENT inline 
void Syscall_frame::timeout(L4_timeout_pair const &to)
{  }

IMPLEMENT inline Utcb *Syscall_frame::utcb() const
{  /*r2*/}

IMPLEMENT inline L4_msg_tag Syscall_frame::tag() const
{  /*r3*/ }

IMPLEMENT inline
void Syscall_frame::tag(L4_msg_tag const &tag)
{  /*r3*/ }

