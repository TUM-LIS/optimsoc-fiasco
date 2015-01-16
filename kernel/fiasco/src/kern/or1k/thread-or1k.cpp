INTERFACE [or1k]:

#include "trap_state.h"

IMPLEMENTATION [or1k]:

extern "C" {

  void pagefault_entry(const Mword pfa, const Mword error_code,
                        const Mword pc, Return_frame *ret_frame)
  {

  }

};

/** Constructor.
    @param space the address space
    @param id user-visible thread ID of the sender
    @param init_prio initial priority
    @param mcp thread's maximum controlled priority
    @post state() != 0
 */
IMPLEMENT
Thread::Thread()
  : Sender(0),  // select optimized version of constructor
    _pager(Thread_ptr::Invalid),
    _exc_handler(Thread_ptr::Invalid),
    _del_observer(0)
{

    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);

}

IMPLEMENT inline
Mword
Thread::user_sp() const
{
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
    return 0;
}

IMPLEMENT inline
void
Thread::user_sp(Mword sp)
{
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
}

IMPLEMENT inline NEEDS[Thread::exception_triggered]
Mword
Thread::user_ip() const
{
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
    return 0;
}

IMPLEMENT inline
Mword
Thread::user_flags() const
{
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
    return 0;
}

IMPLEMENT inline NEEDS[Thread::exception_triggered]
void
Thread::user_ip(Mword ip)
{
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
}

PRIVATE static
void
Thread::print_page_fault_error(Mword e)
{
    (void) e;
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
}

IMPLEMENT
void
Thread::user_invoke()
{
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
}

PUBLIC inline
void FIASCO_NORETURN
Thread::fast_return_to_user(Mword ip, Mword sp, Vcpu_state *arg)
{
    (void) ip; (void) sp; (void) arg;
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
}

IMPLEMENT inline
bool Thread::handle_sigma0_page_fault(Address pfa)
{
    (void) pfa;
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
    return false;
}


PRIVATE static inline
void
Thread::save_fpu_state_to_utcb(Trap_state *ts, Utcb *u)
{
    (void) ts; (void) u;
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
}

bool FIASCO_WARN_RESULT
Thread::copy_utcb_to_ts(L4_msg_tag const &tag, Thread *snd, Thread *rcv,
                        L4_fpage::Rights rights)
{
    (void) tag; (void) snd; (void) rcv; (void) rights;
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
    return false;
}

PRIVATE static inline
bool FIASCO_WARN_RESULT
Thread::copy_ts_to_utcb(L4_msg_tag const &tag, Thread *snd, Thread *rcv,
                        L4_fpage::Rights rights)
{
    (void) tag; (void) snd; (void) rcv; (void) rights;
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
    return false;
}

PUBLIC inline NEEDS ["trap_state.h"]
int
Thread::send_exception_arch(Trap_state *)
{
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
  // nothing to tweak on ARM, TODO: on OR1K?
  return 1;
}

PROTECTED inline
int
Thread::do_trigger_exception(Entry_frame *r, void *ret_handler)
{
    (void) r; (void) ret_handler;
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
  return 0;
}

PROTECTED inline
int
Thread::sys_control_arch(Utcb *)
{
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
  return 0;
}
