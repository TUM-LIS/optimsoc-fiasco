INTERFACE [or1k]:

#include <string.h>
#include "cstdio"

EXTENSION class Config
{
public:
  enum
  {
    // We cannot access the user memory directly
    Access_user_mem = No_access_user_mem,

    // The shift is given by the architecture specification (8kB pages)
    PAGE_SHIFT = ARCH_PAGE_SHIFT,
    PAGE_SIZE  = 1 << PAGE_SHIFT,
    PAGE_MASK  = ~(PAGE_SIZE - 1),

    SUPERPAGE_SHIFT = 24,
    SUPERPAGE_SIZE  = 1 << SUPERPAGE_SHIFT,
    SUPERPAGE_MASK  = ~(SUPERPAGE_SIZE -1),
    hlt_works_ok = 1,
    Irq_shortcut = 0, //TODO: set
  };

  enum
  {
    Kmem_size     = 4*1024*1024, //4 MB
  };

  enum
  {
    Scheduler_one_shot		= 0,
    Scheduler_granularity	= 1000UL,
    Default_time_slice	        = 10 * Scheduler_granularity,
  };

  static unsigned const default_console_uart = 3;
  static unsigned const default_console_uart_baudrate = 115200;
  static const char char_micro;
};


//---------------------------------------------------------------------------
IMPLEMENTATION [or1k]:

char const Config::char_micro = '\265';
const char *const Config::kernel_warn_config_string = 0;

IMPLEMENT FIASCO_INIT
void
Config::init_arch()
{
    printf("%s FIXME\n", __PRETTY_FUNCTION__);
}
