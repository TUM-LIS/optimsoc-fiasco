IMPLEMENTATION[or1k && or1ksim]:

#include <or1k_types.h>

IMPLEMENT static
Address Boot_info::uart_base()
{
  return ~0;
}

IMPLEMENT static
Address Boot_info::pic_base()
{
  return ~0;
}

PUBLIC static
Address Boot_info::mbar()
{
  return ~0;
}
