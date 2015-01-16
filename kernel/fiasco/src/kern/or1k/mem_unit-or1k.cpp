INTERFACE [or1k]:

#include "types.h"
#include "processor.h"

namespace Mmu
{

};

class Mem_unit { };

//------------------------------------------------------------------------------
IMPLEMENTATION[or1k]:

#include "spr.h"
#include <stdio.h>

PUBLIC static inline NEEDS["spr.h"]
void
Mem_unit::mmu_enable()
{
    Mword sr = Spr_Sr::read();
    sr |= (1 << Spr_Sr::DME);
    Spr_Sr::write(sr);
    *((int*)0x8fff0000) = 0x1;
}

PUBLIC static inline NEEDS["spr.h",<stdio.h>]
void
Mem_unit::tlb_flush()
{
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
}

/*PUBLIC static inline NEEDS["spr.h",<stdio.h>]
void
Mem_unit::isync()
{
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
}

PUBLIC static inline NEEDS["spr.h",<stdio.h>]
void
Mem_unit::sync()
{
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
}
*/
