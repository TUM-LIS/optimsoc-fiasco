INTERFACE [libuart]:

#include "io_regblock.h"

EXTENSION class Uart
{
  L4::Io_register_block_mmio _regs;
};

IMPLEMENTATION [libuart]:

IMPLEMENT inline Uart::Uart() : _regs(base()) {}

PUBLIC bool Uart::startup()
{ return uart()->startup(&_regs); }


