INTERFACE [or1k]:

#include "types.h"

/*
 * This is the kernel information page.
 * It contains information regarding the platform.
 *
 */

EXTENSION class Kip
{
public:
  struct Platform_info
  {
    char name[16];
    Unsigned32 is_mp;
  };

  /* 0x00 */
  Mword      magic;
  Mword      version;
  Unsigned8  offset_version_strings;
  Unsigned8  fill0[3];
  Unsigned8  kip_sys_calls;
  Unsigned8  fill1[3];

  // wallento: Removed undocumented

  // Memory information
  Mword _mem_info;

  Platform_info platform_info;

  volatile Cpu_time clock;

  Mword      frequency_cpu;
  Mword      frequency_bus;

  Mword      sigma0_sp, sigma0_ip;
  Mword      sigma1_sp, sigma1_ip;
  Mword      root_sp, root_ip;

  Mword      user_ptr;
  Mword      vhw_offset;


  Mword reserved[2];
};

//---------------------------------------------------------------------------
IMPLEMENTATION [or1k && debug]:

IMPLEMENT inline
void
Kip::debug_print_syscalls() const
{}
