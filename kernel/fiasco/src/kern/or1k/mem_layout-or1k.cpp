INTERFACE [or1k]:

#include "initcalls.h"
#include "template_math.h"
#include <config.h>
#include <cstdio>

EXTENSION class Mem_layout
{

public:
  enum Virt_layout : Address
  {
      // TODO: how is this used? It must be referenced in another way in the
      // kernel as the symbol is only used during initialization then
    //Utcb_ptr_page        = 0x2000,
      // TODO: Again only used here
    //Syscalls             = 0x00000c00,
    Tbuf_status_page     = 0x4000,
    //Kernel_start         = 0x6000,   //end phys pool
    User_max             = 0xe0000000,
    Tcbs                 = 0xc0000000,
    Utcb_addr            = User_max - 0x2000,
    utcb_ptr_align       = Tl_math::Ld<sizeof(void*)>::Res,
    Tcbs_end             = 0xe0000000,
    __free_1_start       = 0xec000000,
    __free_1_end         = 0xed000000,
    Map_base             = 0x00000000,
    //Map_end              = 0xf5000000,
    Caps_start           = 0x05000000,
    Caps_end             = 0x0d000000,
    //Kernel_image         = 0xfd000000,
    //Kernel_max           = 0x00000000,
  };

	enum Phys_layout : Address {
		Ram_phys_base	= 0x00000000
	};

  static Address Tbuf_buffer_area;
  static Address Tbuf_ubuffer_area;
public:
  static Address phys_to_pmem(Address addr);

private:
  static unsigned short __ph_to_pm[1<<(32-Config::SUPERPAGE_SHIFT)];
};

//---------------------------------------------------------------------------
INTERFACE [or1k]:

EXTENSION class Mem_layout
{
public:
  enum {
    Uart_base = 0x80000100,
  };
};


// ------------------------------------------------------------------------
IMPLEMENTATION [or1k]:

#include "panic.h"
#include "paging.h"
#include <cstdio>

Address Mem_layout::Tbuf_buffer_area = 0;
Address Mem_layout::Tbuf_ubuffer_area = 0;

unsigned short Mem_layout::__ph_to_pm[1<<(32-Config::SUPERPAGE_SHIFT)];

IMPLEMENT inline NEEDS[<config.h>]
Address
Mem_layout::phys_to_pmem(Address phys)
{
    Address virt = ((unsigned long)__ph_to_pm[phys >> Config::SUPERPAGE_SHIFT])
      << 16;

    if (!virt)
      return ~0UL;

    return virt | (phys & (Config::SUPERPAGE_SIZE-1));;
}

PUBLIC static inline
Address
Mem_layout::pmem_to_phys (Address addr)
{
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
  (void)addr;
  return ~0L;
}

PUBLIC static
void
Mem_layout::add_pmem(Address phys, Address virt, unsigned long size)
{
  for (;size >= Config::SUPERPAGE_SIZE; size -= Config::SUPERPAGE_SIZE)
    {
      __ph_to_pm[phys >> Config::SUPERPAGE_SHIFT] = virt >> 16;
      phys += Config::SUPERPAGE_SIZE;
      virt += Config::SUPERPAGE_SIZE;
    }
}
