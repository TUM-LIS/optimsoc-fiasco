IMPLEMENTATION [or1k && or1ksim]:

#include "io.h"
#include "boot_info.h"

enum Reg_offsets
{
  Gp0_mode  = 0x600,
  Gp0_count = 0x604
};

/**
 * 0815 reset by syscall?
 */
void __attribute__ ((noreturn))
platform_reset(void)
{
	asm volatile ("l.sys 0x100");
  for(;;) ;
}

IMPLEMENTATION [or1k && !or1ksim]:

void __attribute__ ((noreturn))
platform_reset(void)
{
  for(;;);
}

