INTERFACE:

#include "types.h"

//------------------------------------------------------------------------------
IMPLEMENTATION:

#include "mem_layout.h"
#include "kernel_task.h"
#include "mem_space.h"
IMPLEMENT static
void
Sys_call_page::init()
{
    // TODO: I believe we do not need to set this, but I am not sure
    // Is this how we enter a syscall or how we get there?
  //printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
}
