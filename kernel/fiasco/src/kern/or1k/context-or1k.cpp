IMPLEMENTATION [or1k]:

/** Note: TCB pointer is located in sprg1 */

/*
#include <cassert>
#include <cstdio>

#include "l4_types.h"
#include "cpu_lock.h"
#include "lock_guard.h"
#include "space.h"
#include "thread_state.h"
*/

#include "kmem.h"
#include "utcb_support.h"

IMPLEMENT inline
void
Context::spill_user_state()
{
    printf("%s FIXME\n", __PRETTY_FUNCTION__);
}

IMPLEMENT inline
void
Context::fill_user_state()
{
    printf("%s FIXME\n", __PRETTY_FUNCTION__);
}

PROTECTED inline void
Context::arch_setup_utcb_ptr()
{
    printf("%s FIXME\n", __PRETTY_FUNCTION__);
}

IMPLEMENT inline
void
Context::switch_cpu(Context *t)
{
    printf("%s FIXME\n", __PRETTY_FUNCTION__);
    (void)t;
}

/** Thread context switchin.  Called on every re-activation of a
    thread (switch_exec()).  This method is public only because it is 
    called by an ``extern "C"'' function that is called
    from assembly code (call_switchin_context).
 */

IMPLEMENT
void Context::switchin_context(Context *from)
{
    printf("%s FIXME\n", __PRETTY_FUNCTION__);
  (void)from;
}
