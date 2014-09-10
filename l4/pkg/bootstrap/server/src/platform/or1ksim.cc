/**
 * \file   or1ksim.cc
 * \brief  Support for the or1ksim Simulator
 *
 * \date   2010
 * \author Björn Döbel <doebel@os.inf.tu-dresden.de>
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

#include "support.h"
#include <l4/drivers/uart_or1ksim.h>

namespace {
//class Platform_or1ksim : public Platform_base
class Platform_or1ksim : public Platform_single_region_ram
{
  bool probe() { return true; }

  enum {
  };

  long _ram_area_start;
  long _ram_area_size;

  void init()
  {
    static L4::Io_register_block_mmio r(0x02000000); 
    static L4::Uart_or1ksim _uart; 
    _uart.startup(&r); 
/*		while(true) */
/*		{ */
		  _uart.write("Hello World\n", 12);  
/*		} */
		//asm("l.sys 0x815");
    set_stdio_uart(&_uart); 
  }


  void check_device(unsigned *&ahb_idx)
  {
  }

  void print_device(unsigned *&ahb_idx)
  {
  }

/*  void setup_memory_map(l4util_mb_info_t *, Region_list *ram, Region_list *) */
/*  { */
/*      asm ("l.sys 0x0815"); */
/*  } */
};
}

REGISTER_PLATFORM(Platform_or1ksim);
