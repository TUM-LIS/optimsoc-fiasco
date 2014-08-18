IMPLEMENTATION[uart_or1ksim && libuart]:

#include "uart_or1ksim.h"
#include "mem_layout.h"

IMPLEMENT Address Uart::base() const { return Mem_layout::Uart_base; }

IMPLEMENT int Uart::irq() const { return 0; }

IMPLEMENT L4::Uart *Uart::uart()
{
  static L4::Uart_or1ksim uart;
  return &uart;
}
