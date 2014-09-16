INTERFACE [or1k]:

#include "kip.h"

class Kip_init
{
public:
  static void init();
};


//---------------------------------------------------------------------------
IMPLEMENTATION [or1k]:

#include "mem_layout.h"
#include "config.h"

// Make the stuff below apearing only in this compilation unit.
// Trick Preprocess to let the struct reside in the cc file rather
// than putting it into the _i.h file which is perfectly wrong in 
// this case.
namespace KIP_namespace
{
  enum
  {
    Num_mem_descs = 20,
    Max_len_version = 512,

    Size_mem_descs = sizeof(Mword) * 2 * Num_mem_descs,
  };

  struct KIP
  {
    Kip kip;
    char mem_descs[Size_mem_descs];
  };

  KIP my_kernel_info_page asm("my_kernel_info_page") __attribute__((section(".kernel_info_page"))) =
		{
			{
	/* 00/00  */ L4_KERNEL_INFO_MAGIC,
	             Config::Kernel_version_id,
	             (Size_mem_descs + sizeof(Kip)) >> 4, {},
							 0, {},
	/* 10/20  */ 0,    /* Mword _mem_info*/
							 {"", 0}, /* Platform_info aka 16+32=1.5 Words */
							 0,    /* Cpu_time aka 64=2 Words */
							 0,    /* Mword frequency_cpu */
							 0,    /* Mword frequency_bus */
							 0, 0, /* Mword sigma0_sp, sigma0_ip */
							 0, 0, /* Mword sigma1_sp, sigma1_ip */
							 0, 0, /* Mword root_spu, root_ip */
							 0,		 /* mword user_ptr */
							 0,		 /* mword vhw_offset */
							 {}		 /* Mword reserved[2] */
			},
			{}
    };
};


IMPLEMENT
void Kip_init::init()
{
  Kip *kinfo = reinterpret_cast<Kip*>(&KIP_namespace::my_kernel_info_page);
  Kip::init_global_kip(kinfo);

  /* add kernel image */
  kinfo->add_mem_region(Mem_desc(0,(Address)&Mem_layout::end - 1,
                        Mem_desc::Reserved));

  kinfo->add_mem_region(Mem_desc(0, Mem_layout::User_max - 1, 
	                Mem_desc::Conventional, true));
}
