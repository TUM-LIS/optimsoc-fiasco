INTERFACE [or1k]:
#include "types.h"
#include "initcalls.h"
#include "uart.h"
#include "boot_info.h"
#include "terminate.h"
#include "mem_layout.h"
//#include "uart_or1ksim.h"

#include <construction.h>
#include <cstdlib>
#include <cstdio>

IMPLEMENTATION [or1k]:

#include "mem_unit.h"

extern char kernel_page_directory[];

namespace Bootstrap {

struct Order_t;
struct Phys_addr_t;
struct Virt_addr_t;

typedef cxx::int_type<unsigned, Order_t> Order;
typedef cxx::int_type_order<Unsigned32, Virt_addr_t, Order> Virt_addr;
typedef cxx::int_type_order<Unsigned32, Phys_addr_t, Order> Phys_addr;

enum
{
  Virt_ofs = Mem_layout::Ram_phys_base - Mem_layout::Map_base,
};

inline Order map_page_order() { return Order(13); }

inline Phys_addr pt_entry(Phys_addr pa)
{
    Phys_addr res = pa;
  return res;
}

static void
map_memory(void volatile *pd, Virt_addr va, Phys_addr pa)
{
  Phys_addr *const p = (Phys_addr*)pd;
  p[cxx::int_value<Virt_addr>(va >> map_page_order())]
    = pt_entry(pa);
}
}

extern "C" int main(void);

extern "C" FIASCO_INIT 
int bootstrap_main()
{
   Bootstrap::Virt_addr va;
   Bootstrap::Phys_addr pa;
   /* map phys mem starting from VA 0xF0000000 */
   va = Bootstrap::Virt_addr(Mem_layout::Map_base);
   pa = Bootstrap::Phys_addr(Mem_layout::Ram_phys_base);
   Bootstrap::map_memory(kernel_page_directory, va, pa);
   /* map phys mem 1:1 as well */
   va = Bootstrap::Virt_addr(Mem_layout::Ram_phys_base);
   pa = Bootstrap::Phys_addr(Mem_layout::Ram_phys_base);
   Bootstrap::map_memory(kernel_page_directory, va, pa);

   // The first 32MB of phys memory are always mapped to Map_base
   Mem_layout::add_pmem(Mem_layout::Ram_phys_base, Mem_layout::Map_base,
                        32 << 20);


   static_construction();
    printf("Starting Bootstrapping\n");
  atexit(&static_destruction);
	printf("Bootstrapped\n");
	   Mem_unit::mmu_enable();
  terminate(main());
  return 0;
}

