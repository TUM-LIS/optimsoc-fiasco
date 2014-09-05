/*
 * (c) 20414 Stefan Wallentowitz <stefan.wallentowitz@tum.de>
 * This file is part of TUD:OS and distributed under the terms of the
 * GNU Lesser General Public License 2.1.
 * Please see the COPYING-LGPL-2.1 file for details.
 */

#include "support.h"

void
reboot_arch(void) __attribute__((noreturn));

void
reboot_arch(void)
{
  Platform_base::platform->reboot();

  while (1)
    ;
}
