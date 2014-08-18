/**
 * \file   support_sparc_leon3.cc
 * \brief  Support for the Sparc LEON3 platform
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

namespace {
class Platform_or1ksim : public Platform_base
{
  bool probe() { return true; }

  enum {
  };

  long _ram_area_start;
  long _ram_area_size;

  void init()
  {
  }


  void check_device(unsigned *&ahb_idx)
  {
  }

  void print_device(unsigned *&ahb_idx)
  {
  }

  void setup_memory_map(l4util_mb_info_t *, Region_list *ram, Region_list *)
  {
      asm ("l.trap");
  }
};
}

REGISTER_PLATFORM(Platform_leon3);
