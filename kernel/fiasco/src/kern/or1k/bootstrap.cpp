INTERFACE [or1k]:
#include "types.h"
#include "initcalls.h"

IMPLEMENTATION [or1k]:
#include "uart.h"
#include "boot_info.h"
#include "terminate.h"
#include "mem_layout.h"
//#include "uart_or1ksim.h"

#include <construction.h>
#include <cstdlib>
#include <cstdio>

/*extern "C" void __attribute__ ((noreturn))
_exit(int)
{
  printf("Exiting\n");
  while(1){};
}
*/

namespace Bootstrap {

static void
add_initial_pmem()
{
	// layout specific physical address is mapped to Map_base
	// need 4MB
	Mem_layout::add_pmem(Mem_layout::Ram_phys_base, Mem_layout::Map_base, 4<<20);
}
}

extern "C" int main(void);

extern "C" FIASCO_INIT 
int bootstrap_main(void * /* r3 */, Address prom_ptr /* r4 */)
{
	Boot_info::init();
	Bootstrap::add_initial_pmem();
	printf("Starting Bootstrapping\n");
  atexit(&static_destruction);
  static_construction();
	printf("Bootstrapped\n");
  terminate(main());
  return 0;
}

