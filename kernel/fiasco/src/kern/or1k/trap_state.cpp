
INTERFACE:

#include "l4_types.h"
#include "entry_frame.h"

class Trap_state_regs
{
public:
  Mword pf_address;
  Mword error_code;
};


class Trap_state : public Trap_state_regs, public Syscall_frame,
                   public Return_frame
{
public:
  typedef int (*Handler)(Trap_state*, Cpu_number cpu);
  bool exclude_logging() { return false; }
};


IMPLEMENTATION:

#include <cstdio>

PUBLIC inline
void
Trap_state::sanitize_user_state()
{
  // implement me
}

PUBLIC inline
unsigned long
Trap_state::ip() const
{ }

PUBLIC inline
unsigned long
Trap_state::trapno() const
{ }

PUBLIC inline
Mword
Trap_state::error() const
{  }

PUBLIC inline
void
Trap_state::set_ipc_upcall()
{

}

PUBLIC inline
void
Trap_state::set_pagefault(Mword pfa, Mword error)
{

}

PUBLIC inline
bool
Trap_state::is_debug_exception() const
{ }

PUBLIC
void
Trap_state::dump()
{

}

