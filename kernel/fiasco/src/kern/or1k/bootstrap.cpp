INTERFACE [or1k]:
#include "types.h"
#include "initcalls.h"

IMPLEMENTATION [or1k]:
#include "uart.h"
#include "boot_info.h"
#include "terminate.h"
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

extern "C" int main(void);

extern "C" FIASCO_INIT 
int bootstrap_main(void * /* r3 */, Address prom_ptr /* r4 */)
{
	Boot_info::init();
	printf("Starting Bootstrapping\n");
  atexit(&static_destruction);
  static_construction();
	printf("Bootstrapped\n");
  terminate(main());
  return 0;
}

