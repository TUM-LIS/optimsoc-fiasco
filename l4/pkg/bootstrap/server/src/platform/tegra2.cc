/*!
 * \file
 * \brief  Support for Tegra 2 platforms
 *
 * \date   2010-05
 * \author Adam Lackorzynski <adam@os.inf.tu-dresden.de>
 *
 */
/*
 * (c) 2010 Author(s)
 *     economic rights: Technische Universität Dresden (Germany)
 *
 * This file is part of TUD:OS and distributed under the terms of the
 * GNU General Public License 2.
 * Please see the COPYING-GPL-2 file for details.
 */

/* Init-code from http://android.git.kernel.org/?p=kernel/tegra.git */

#include "support.h"
#include <l4/drivers/uart_pxa.h>

namespace {
class Platform_arm_tegra2 : public Platform_single_region_ram
{
  void some_delay(int d) const
    {
      for (int i = 0; i <  d; i++)
        asm volatile("":::"memory");
    }

  bool probe() { return true; }

  void init()
  {
    volatile unsigned long *addr;

    addr = (volatile unsigned long *)0x600060a0;
    *addr = 0x5011b00c;

    /* PLLP_OUTA_0 */
    addr = (volatile unsigned long *)0x600060a4;
    *addr = 0x10031c03;

    /* PLLP_OUTB_0 */
    addr = (volatile unsigned long *)0x600060a8;
    *addr = 0x06030a03;

    /* PLLP_MISC_0 */
    addr = (volatile unsigned long *)0x600060ac;
    *addr = 0x00000800;

    some_delay(1000000);

    /* UARTD clock source is PLLP_OUT0 */
    addr = (volatile unsigned long *)0x600061c0;
    *addr = 0;

    /* Enable clock to UARTD */
    addr = (volatile unsigned long *)0x60006018;
    *addr |= 2;
    some_delay(5000);

    /* Deassert reset to UARTD */
    addr = (volatile unsigned long *)0x6000600c;
    *addr &= ~2;

    some_delay(5000);

    static L4::Uart_16550 _uart(13478400);
    static L4::Io_register_block_mmio r(0x70006300, 2);
    _uart.startup(&r);
    _uart.change_mode(3, 115200);
    set_stdio_uart(&_uart);
  }
};
}

REGISTER_PLATFORM(Platform_arm_tegra2);
