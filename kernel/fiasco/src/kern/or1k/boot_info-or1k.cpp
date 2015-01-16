INTERFACE [or1k]:

#include "types.h"
//#include "or1k_types.h"

EXTENSION class Boot_info 
{
  public:
    /**
     * Return memory-mapped base address of uart/pic
     */
    static Address uart_base();
};


//------------------------------------------------------------------------------
IMPLEMENTATION [or1k]:

#include "boot_info.h"
#include "stdio.h"
#include <string.h>

IMPLEMENT static 
void Boot_info::init()
{
    // TODO: I think we do not need anything here for the moment
    //printf("(NOT IMPLEMENTED) Boot_info::init not implemented (%s)\n", __FILE__);
}


