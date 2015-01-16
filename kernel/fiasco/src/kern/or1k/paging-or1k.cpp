INTERFACE[or1k]:

#include "types.h"
#include "config.h"

// TODO: Why include here? Should be included in paging.cpp
#include "ptab_base.h"

/**
 * Page Fault
 */
class PF {};

/**
 * Page
 */
class Page {
};

/**
 * Page table entry
 */
class Pte_ptr
{
public:
    Pte_ptr() = default;
    Pte_ptr(void *p, unsigned char level) { (void) p; (void) level; printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__); }

    enum { Super_level = 0 };
    bool is_valid() const { printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__); return false; }
    bool is_leaf() const { printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__); return false; }
    Mword next_level() const
    {
        printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
      return 0;
    }
    void set_next_level(Mword phys)
    {
      (void) phys;
      printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
    }

    unsigned char page_order() const
    {
        printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
        return 0;
    }


    Mword page_addr() const { return printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__); return 0; }
    void clear() { printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__); }
    static inline void write_back(void *, void *) { printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__); }
    inline void write_back_if(bool) { printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__); }
};

// Trait parameters
//  - Type
//  - Shift
//  - Number of bits
//  - May be leaf
typedef Ptab::List< Ptab::Traits< Unsigned32, 24, 8, false>,
                    Ptab::Traits< Unsigned32, 13, 11, true> > Ptab_traits;

typedef Ptab::Shift<Ptab_traits, Virt_addr::Shift>::List Ptab_traits_vpn;
typedef Ptab::Page_addr_wrap<Page_number, Virt_addr::Shift> Ptab_va_vpn;

//------------------------------------------------------------------------------
IMPLEMENTATION[or1k]:

IMPLEMENT inline
Mword PF::addr_to_msgword0( Address pfa, Mword error )
{
    (void) pfa; (void) error;
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
  return 0;
}

IMPLEMENT inline
Mword PF::is_usermode_error( Mword error )
{
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
    return 0;
}
