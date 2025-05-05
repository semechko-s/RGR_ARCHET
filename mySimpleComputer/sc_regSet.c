#include "../include/mySimpleComputer.h"

int
sc_regSet (int reg, int value)
{
  if ((reg < FLAG_OVERFLOW_OPERATION) || (reg > FLAG_INVALID_COMMAND))
    {
      printf ("Invalid register\n");
      return -1;
    }
  if (value == 0)
    {
      flags = flags & (~(1 << (reg - 1)));
    }
  else
    {
      flags = flags | (1 << (reg - 1));
    }
  return 0;
}