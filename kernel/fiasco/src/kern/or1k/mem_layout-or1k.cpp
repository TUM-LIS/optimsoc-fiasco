INTERFACE [or1k]:

#include "initcalls.h"
#include "template_math.h"
#include <config.h>
#include <cstdio>

EXTENSION class Mem_layout
{

//TODO cbass: check what can be omitted
public:
  enum Virt_layout : Address
  {
    Utcb_ptr_page        = 0x3000,
    Syscalls_phys        = 0x4000,
    Tbuf_status_page     = 0x5000,
    Kernel_start         = 0x6000,   //end phys pool
    Syscalls             = 0x00000c00,
    User_max             = 0xf0000000,
    Tcbs                 = 0xc0000000,
    Utcb_addr            = User_max - 0x2000,
    utcb_ptr_align       = Tl_math::Ld<sizeof(void*)>::Res,
    Tcbs_end             = 0xe0000000,
    __free_1_start       = 0xec000000,
    __free_1_end         = 0xed000000,
    Map_base             = 0xf0000000, ///< % 80MB kernel memory
    Map_end              = 0xf5000000,
    Caps_start           = 0xf5000000,
    Caps_end             = 0xfd000000,
    Kernel_image         = 0xfd000000,
    Kernel_max           = 0x00000000,
  };

	enum Phys_layout : Address {
		Ram_phys_base	= 0x10000000
	};

  static Address Tbuf_buffer_area;
  static Address Tbuf_ubuffer_area;
public:
	static void add_pmem(Address phys, Address virt, unsigned long size);

private:
  static unsigned short __ph_to_pm[1UL<<(32-Config::SUPERPAGE_SHIFT)];
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

PUBLIC static
Address
Mem_layout::phys_to_pmem (Address addr)
{
	printf("phys_to_pmem\t addr: %10lx\n", addr >> Config::SUPERPAGE_SHIFT);
  Address virt = ((unsigned long)__ph_to_pm[addr >> Config::SUPERPAGE_SHIFT]) << 16;
	
	printf("phys_to_pmem\t virt: %10lx\n", virt);

  if (!virt)
  {
    return ~0UL;
  }

  return virt | (addr & (Config::SUPERPAGE_SIZE-1));
}

// add a pair of physical and virtual memory page to the array were such information is stored
IMPLEMENT inline NEEDS[<config.h>]
void
Mem_layout::add_pmem(Address phys, Address virt, unsigned long size)
{
	// do it page wise
	for(;size >= Config::SUPERPAGE_SIZE; size -= Config::SUPERPAGE_SIZE)
	{
		printf("Mem_layout::add_pmem: added phys: %10lx to virt: %10lx\n", phys >> Config::SUPERPAGE_SHIFT, virt >> 16);
		printf("Mem_layout::add_pmem(non shortend): added phys: %10lx to virt: %10lx\n", phys, virt);
		// only the upper bits are important
		__ph_to_pm[phys >> Config::SUPERPAGE_SHIFT] = virt >> 16;
		// go to next page
		phys += Config::SUPERPAGE_SIZE;
		virt += Config::SUPERPAGE_SIZE;
	}
}

PUBLIC static inline
Address
Mem_layout::pmem_to_phys (Address addr)
{
  (void)addr;
  return ~0L;
}

PUBLIC static inline
Address
Mem_layout::pmem_to_phys (const void *ptr)
{
  return reinterpret_cast<Address>(ptr);
}

PUBLIC static inline
template< typename V >
bool
Mem_layout::read_special_safe(V const * /* *address */, V &/*v*/)
{
  panic("%s not implemented", __PRETTY_FUNCTION__);
  return false;
}

PUBLIC static inline
template< typename T >
T
Mem_layout::read_special_safe(T const *a)
{
  Mword res;
  return T(res);
}


/* no page faults can occur, return true */
PUBLIC static inline
bool
Mem_layout::is_special_mapped(void const * /*a*/)
{
    printf("\x1b[31mMem_layout::is_special_mapped returns true\n\x1b[0m");
  return true;
}


IMPLEMENTATION [or1k && debug]:

#include "kip_init.h"


PUBLIC static FIASCO_INIT
void
Mem_layout::init()
{
  Mword alloc_size = 0x200000;
  unsigned long max = ~0UL;
  for (;;)
    {
      Mem_region r; r.start=2;r.end=1;// = Kip::k()->last_free(max);
      if (r.start > r.end)
        panic("Corrupt memory descscriptor in KIP...");

      if (r.start == r.end)
        panic("not enough kernel memory");

      max = r.start;
      Mword size = r.end - r.start + 1;
      if(alloc_size <= size)
	{
	  r.start += (size - alloc_size);
	  Kip::k()->add_mem_region(Mem_desc(r.start, r.end,
	                                    Mem_desc::Reserved));

	  printf("TBuf  installed at: [%08lx; %08lx] - %lu KB\n", 
	         r.start, r.end, alloc_size / 1024);

	  Tbuf_buffer_area = Tbuf_ubuffer_area = r.start;
	  break;
	}
    }

    if(!Tbuf_buffer_area)
      panic("Could not allocate trace buffer");
}

IMPLEMENTATION [or1k && !debug]:

PUBLIC static FIASCO_INIT
void
Mem_layout::init()
{}
