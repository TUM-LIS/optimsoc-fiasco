/*
 * (c) 20414 Stefan Wallentowitz <stefan.wallentowitz@tum.de>
 * This file is part of TUD:OS and distributed under the terms of the
 * GNU Lesser General Public License 2.1.
 * Please see the COPYING-LGPL-2.1 file for details.
 */

#include <spr-defs.h>

_reboot_arch:
    l.ori   r1, r0, 0x100
    l.mtspr r0, r1, SPR_EPCR_BASE
    l.rfe
    l.nop
