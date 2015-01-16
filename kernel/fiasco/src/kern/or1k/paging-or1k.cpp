INTERFACE[or1k]:

#include "types.h"
#include "config.h"

class PF {};
class Page {};

//------------------------------------------------------------------------------
INTERFACE[or1k]:

#include <cassert>
#include "types.h"
#include "ptab_base.h"
#include "kdb_ke.h"
#include "mem_unit.h"

class Paging {};

class Pte_ptr
{
public:
  typedef Mword Entry;

  Pte_ptr() = default;
  Pte_ptr(void *p, unsigned char level) : pte((Mword*)p), level(level) {}

  bool is_valid() const { return *pte & Valid; }

  void clear() { *pte = 0; }

  bool is_leaf() const
  {
    return false; // FIX
  }

  Mword next_level() const
  {
    return cxx::mask_lsb(*pte, 10); // copy'n'paste, check and fix!
  };

  void set_next_level(Mword phys)
  {
    write_now(pte, phys | 1); // copy'n'paste, check and fix!
  }

  unsigned char page_order() const
  {
    // Check and fix!
    if (level == 0)
      return 20;
    return 12;
  }

  Mword page_addr() const
  { return cxx::mask_lsb(*pte, page_order()); } // copy'n'paste, check and fix!

  enum
  {
    ET_ptd         = 1,           ///< PT Descriptor is PTD
    ET_pte         = 2,           ///< PT Descriptor is PTE

    Ptp_mask       = 0xfffffffc,  ///< PTD: page table pointer
    Ppn_mask       = 0xffffff00,  ///< PTE: physical page number
    Ppn_addr_shift = 4,           ///< PTE/PTD: need to shift phys addr
    Cacheable      = 0x80,        ///< PTE: is cacheable
    Modified       = 0x40,        ///< PTE: modified
    Referenced     = 0x20,        ///< PTE: referenced
    Accperm_mask   = 0x1C,        ///< 3 bits for access permissions
    Accperm_shift  = 2,
    Et_mask        = 0x3,         ///< 2 bits to determine entry type
    Vfpa_mask      = 0xfffff000,  ///< Flush/Probe: virt. addr. mask
    Flushtype_mask = 0xf00,       ///< Flush/Probe: type

    Pdir_mask        = 0xFF,
    Pdir_shift       = 24,
    Ptab_mask        = 0x3F,
    Ptab_shift1      = 18,
    Ptab_shift2      = 12,
    Page_offset_mask = 0xFFF,

    Super_level    = 0,
    Valid          = 0x3,
  };

  Mword *pte;
  unsigned char level;

  //  Mword addr() const { return _raw & Ppn_mask;}
    //bool is_super_page() const { return _raw & Pse_bit; }
};

#if 0
class Pt_entry : public Pte_base
{
public:
  Mword leaf() const { return true; }
  void set(Address p, bool /*intermed*/, bool /*present*/, unsigned long attrs = 0)
  {
    _raw = ((p >> Ppn_addr_shift) & Ppn_mask) | attrs | ET_pte;
  }
};

class Pd_entry : public Pte_base
{
public:
  Mword leaf() const { return false; }
  void set(Address p, bool /*intermed*/, bool /*present*/, unsigned long /*attrs*/ = 0)
  {
    _raw = ((p >> Ppn_addr_shift) & Ptp_mask) | ET_ptd;
  }
};
#endif

#if 0
namespace Page
{
  typedef Unsigned32 Attribs;
  enum Attribs_enum
  {
    Cache_mask   = 0x00000078,
    CACHEABLE    = 0x00000000,
    NONCACHEABLE = 0x00000040,
    BUFFERED     = 0x00000080, //XXX not sure
  };
};
#endif


typedef Ptab::List< Ptab::Traits<Unsigned32, 22, 10, true>,
                    Ptab::Traits<Unsigned32, 12, 10, true> > Ptab_traits;

typedef Ptab::Shift<Ptab_traits, Virt_addr::Shift>::List Ptab_traits_vpn;
typedef Ptab::Page_addr_wrap<Page_number, Virt_addr::Shift> Ptab_va_vpn;


IMPLEMENTATION[or1k]:

/*#include "psr.h" */
#include "lock_guard.h"
#include "cpu_lock.h"
#include "kip.h"


/* this functions do nothing on SPARC architecture */
PUBLIC static inline
Address
Paging::canonize(Address addr)
{
  return addr;
}

PUBLIC static inline
Address
Paging::decanonize(Address addr)
{
  return addr;
}

IMPLEMENT inline
Mword PF::is_translation_error(Mword error)
{
  return !(error & 1 << 30) /* DSISR/SRR1 bit 1 */;
}

IMPLEMENT inline //NEEDS["psr.h"]
Mword PF::is_usermode_error(Mword error)
{
  return 0 & error;//(error & Msr::Msr_pr);
}

IMPLEMENT inline
Mword PF::is_read_error(Mword error)
{
  return !(error & (1 << 25)) /* DSISR bit 6*/;
}

IMPLEMENT inline
Mword PF::addr_to_msgword0(Address pfa, Mword error)
{
  Mword a = pfa & ~3;
  if(is_translation_error(error))
    a |= 1;
  if(!is_read_error(error))
    a |= 2;
  return a;
}

PUBLIC static inline
bool
Pte_ptr::need_cache_write_back(bool current_pt)
{ return true; /*current_pt;*/ (void)current_pt; }

PUBLIC inline NEEDS["mem_unit.h"]
void
Pte_ptr::write_back_if(bool current_pt, Mword /*asid*/ = 0)
{
  (void)current_pt;
  //if (current_pt)
  //  Mem_unit::clean_dcache(pte);
}

PUBLIC static inline NEEDS["mem_unit.h"]
void
Pte_ptr::write_back(void *start, void *end)
{ (void)start; (void)end; }



PUBLIC static
void
Paging::init()
{
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
}
