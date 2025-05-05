#include "../include/mySimpleComputer.h"

int
sc_regGet (int reg, int *value)
{
  if ((reg < FLAG_OVERFLOW_OPERATION) || (reg > FLAG_INVALID_COMMAND)
      || (value == NULL))
    {
      printf ("Invalid register\n");
      return -1;
    }
  *value = (flags >> (reg - 1)) & 0x1;
  return 0;
}