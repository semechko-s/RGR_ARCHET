#include "../include/mySimpleComputer.h"

int
sc_commandEncode (int sign, int command, int operand, int *value)
{
  if ((sign > 1 || sign < 0) || (operand > 127 || operand < 0)
      || (sc_commandValidate (command) == -1))
    {
      return -1;
    }

  if ((command > 0 && command < 10) || (command > 11 && command < 20)
      || (command > 21 && command < 30) || (command > 33 && command < 40)
      || (command > 44 && command < 51) || command > 79)
    {
      sc_regSet (FLAG_INVALID_COMMAND, 1);
      return 1;
    }

  for (int i = 0; i <= 14; i++)
    {
      *value = *value & (~(1 << (i - 1)));
    }

  int bit = 0;
  bit = ((sign >> 0) & 0x1);
  if (bit)
    {
      *value = *value | (1 << (14));
    }
  else
    {
      *value = *value & (~(1 << (14 - 1)));
    }

  for (int i = 8; i <= 14; i++)
    {
      bit = 0;
      bit = ((command >> (i - 7 - 1)) & 0x1);
      if (bit)
        {
          *value = *value | (1 << (i - 1));
        }
      else
        {
          *value = *value & (~(1 << (i - 1)));
        }
    }

  for (int i = 1; i <= 7; i++)
    {
      bit = 0;
      bit = ((operand >> (i - 1)) & 0x1);
      if (bit)
        {
          *value = *value | (1 << (i - 1));
        }
      else
        {
          *value = *value & (~(1 << (i - 1)));
        }
    }
}