INTERFACE:

#include "types.h"

#include <or1k-support.h>
#include <spr-defs.h>

class Spr_Sr
{
public:
  enum Spr_Sr_bits {
      CID   = 28, // Context ID
      SUMRA = 16, // SPRs User Mode Read Access
      FO    = 15, // Fixed One
      EPH   = 14, // Exception Prefix High
      DSX   = 13, // Delay Slot Exception
      OVE   = 12, // Overflow Flag Exception
      OV    = 11, // Overflow Flag
      CY    = 10, // Carry Flag
      F     = 9,  // Flag
      CE    = 8,  // CID Enable
      LEE   = 7,  // Little Endian Enable
      IME   = 6,  // Instruction MMU Enable
      DME   = 5,  // Data MMU Enable
      ICE   = 4,  // Instruction Cache Enable
      DCE   = 3,  // Data Cache Enable
      IEE   = 2,  // Interrupt Exception Enable
      TEE   = 1,  // Timer Exception Enable
      SM    = 0,  // Supervisor Mode
  };

  enum Spr_Sr_masks {
	  CID_mask = 0xF,
  };
};

//------------------------------------------------------------------------------
IMPLEMENTATION:

PUBLIC static inline 
Mword
Spr_Sr::read()
{
  return or1k_mfspr(SPR_SR);
}


PUBLIC static inline
void
Spr_Sr::write(unsigned sr)
{
    or1k_mtspr(SPR_SR, sr);
}
