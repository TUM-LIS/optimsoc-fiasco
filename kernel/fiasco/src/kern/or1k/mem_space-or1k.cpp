INTERFACE [or1k]:

#include "entry_frame.h"
#include "mem_unit.h"

extern "C"
void
pagefault_entry(Mword, Mword);

EXTENSION class Mem_space
{
public:

  typedef Pdir Dir_type;

  /** Return status of v_insert. */
  enum //Status 
  {
    Insert_ok = 0,		///< Mapping was added successfully.
    Insert_warn_exists,		///< Mapping already existed
    Insert_warn_attrib_upgrade,	///< Mapping already existed, attribs upgrade
    Insert_err_nomem,		///< Couldn't alloc new page table
    Insert_err_exists		///< A mapping already exists at the target addr
  };

  /** Attribute masks for page mappings. */
  enum Page_attrib
    {
      Page_no_attribs = 0,
      /// Page is writable.
      Page_writable = 0, // XXX
      Page_cacheable = 0,
      /// Page is noncacheable.
      Page_noncacheable = 0, // XXX
      /// it's a user page.
      Page_user_accessible = 0, // XXX
    };

  // Mapping utilities
  enum				// Definitions for map_util
  {
    Need_insert_tlb_flush = 0,
    Map_page_size = Config::PAGE_SIZE,
    Page_shift = Config::PAGE_SHIFT,
    Map_max_address = Mem_layout::User_max,
    Whole_space = MWORD_BITS,
    Identity_map = 0,
  };

protected:
  // DATA
  Dir_type *_dir;
};


//----------------------------------------------------------------------------
IMPLEMENTATION [or1k]:

#include <cstring>
#include <cstdio>
#include "cpu.h"
#include "kdb_ke.h"
#include "l4_types.h"
#include "mem_layout.h"
#include "paging.h"
#include "std_macros.h"
#include "kmem.h"
#include "kmem_alloc.h"
#include "logdefs.h"
#include "panic.h"
#include "lock_guard.h"
#include "cpu_lock.h"
#include "warn.h"




PUBLIC explicit inline
Mem_space::Mem_space(Ram_quota *q) : _quota(q), _dir(0) {
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
}

PROTECTED inline
bool
Mem_space::initialize()
{
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
}

PUBLIC
Mem_space::Mem_space(Ram_quota *q, Dir_type* pdir)
  : _quota(q), _dir(pdir)
{
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
}

IMPLEMENT inline
void
Mem_space::make_current()
{
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
}


PROTECTED inline
void
Mem_space::sync_kernel()
{
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
}


IMPLEMENT inline NEEDS ["kmem.h"]
void Mem_space::switchin_context(Mem_space *from)
{
  (void)from;
  printf("%s FIXME\n", __PRETTY_FUNCTION__);
}

PUBLIC static inline
bool
Mem_space::is_full_flush(L4_fpage::Rights rights)
{
    printf("%s FIXME\n", __func__);
  return rights & L4_fpage::Rights::R();
}

PUBLIC inline NEEDS["cpu.h"]
static bool
Mem_space::has_superpages()
{
    printf("%s FIXME\n", __func__);
  return Cpu::have_superpages();
}

//we flush tlb in htab implementation
PUBLIC static inline
void
Mem_space::tlb_flush(bool x)
{
    (void) x;
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
  //Mem_unit::tlb_flush();
}

PUBLIC static inline
void
Mem_space::tlb_flush_spaces(bool all, Mem_space *s1, Mem_space *s2)
{
    (void) all; (void) s1; (void) s2;
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
}

/*
PUBLIC inline
bool 
Mem_space::set_attributes(Address virt, unsigned page_attribs)
{*/
/*
  Pdir::Iter i = _dir->walk(virt);

  if (!i.e->valid() || i.shift() != Config::PAGE_SHIFT)
    return 0;

  i.e->del_attr(Page::MAX_ATTRIBS);
  i.e->add_attr(page_attribs);
  return true;
*/
/*  NOT_IMPL_PANIC;
  return false;
}*/

PROTECTED inline
void
Mem_space::destroy()
{
    printf("%s FIXME\n", __func__);
}

/**
 * Destructor.  Deletes the address space and unregisters it from
 * Space_index.
 */
PRIVATE
void
Mem_space::dir_shutdown()
{
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
}

IMPLEMENT inline
Mem_space *
Mem_space::current_mem_space(Cpu_number cpu) /// XXX: do not fix, deprecated, remove!
{
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
}

IMPLEMENT inline
Mem_space::Status
Mem_space::v_insert(Phys_addr phys, Vaddr virt, Page_order size,
		    Attr page_attribs)
{
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
}


PUBLIC inline NEEDS ["paging.h"]
Address
Mem_space::virt_to_phys (Address virt) const
{
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
}

PUBLIC inline
virtual Address
Mem_space::virt_to_phys_s0(void *a) const
{
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
}

PUBLIC inline
Address
Mem_space::pmem_to_phys (Address virt) const
{
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
}



/** Look up a page-table entry.
    @param virt Virtual address for which we try the look up.
    @param phys Meaningful only if we find something (and return true).
                If not 0, we fill in the physical address of the found page
                frame.
    @param page_attribs Meaningful only if we find something (and return true).
                If not 0, we fill in the page attributes for the found page
                frame (see Mem_space::Page_attrib).
    @param size If not 0, we fill in the size of the page-table slot.  If an
                entry was found (and we return true), this is the size
                of the page frame.  If no entry was found (and we
                return false), this is the size of the free slot.  In
                either case, it is either 4KB or 4MB.
    @return True if an entry was found, false otherwise.
 */
IMPLEMENT
bool
Mem_space::v_lookup(Vaddr virt, Phys_addr *phys, Page_order *order,
		    Attr *page_attribs)
{
    printf("%s FIXME\n", __func__);

}

/** Delete page-table entries, or some of the entries' attributes.  This
    function works for one or multiple mappings (in contrast to v_insert!).
    @param virt Virtual address of the memory region that should be changed.
    @param size Size of the memory region that should be changed.
    @param page_attribs If nonzero, delete only the given page attributes.
                        Otherwise, delete the whole entries.
    @return Combined (bit-ORed) page attributes that were removed.  In
            case of errors, ~Page_all_attribs is additionally bit-ORed in.
 */
IMPLEMENT
L4_fpage::Rights
Mem_space::v_delete(Vaddr virt, Page_order size,
		    L4_fpage::Rights page_attribs)
{
    printf("%s FIXME\n", __func__);

}

PUBLIC static inline
Page_number
Mem_space::canonize(Page_number v)
{  printf("%s FIXME\n", __func__);
 return v; }

PUBLIC static
void
Mem_space::init_page_sizes()
{
    printf("%s FIXME\n", __func__);

}

IMPLEMENT inline
void
Mem_space::v_set_access_flags(Vaddr va, L4_fpage::Rights)
{
    (void) va;
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
}
