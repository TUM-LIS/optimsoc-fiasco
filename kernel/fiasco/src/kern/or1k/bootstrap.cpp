INTERFACE [or1k]:
#include "types.h"
#include "initcalls.h"

IMPLEMENTATION [or1k]:
#include "uart.h"
#include "boot_info.h"
#include "terminate.h"
#include "uart_or1ksim.h"

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
//extern char _vectors;
//char *foo = &_vectors;

extern "C" FIASCO_INIT 
int bootstrap_main(void * /* r3 */, Address prom_ptr /* r4 */)
{
	/*asm volatile ("l.movhi r15, hi(%0)"
								:
								:"r" (_vectors));
	asm volatile ("l.ori r15,r15, lo(%0)"
								:
								:"r" (_vecotrs));*/
	//  Boot_info::init();
	L4::Io_register_block_mmio r(0x80000100);
	L4::Uart_or1ksim blub;
	blub.startup(&r);

	blub.write("\nBOTSTRAPING MAIN\n",18 );
	printf("FOOOOOUO\n");

  atexit(&static_destruction);
  static_construction();
  blub.write("Bootstrapped\n",13);
  terminate(main());
  return 0;
}

