#include "../include/mySimpleComputer.h"

int
sc_commandDecode (int value, int *sign, int *command, int *operand)
{
  if (value > 32767)
    {
      return -1;
    }

  int bit = 0;
  bit = ((value >> 14) & 0x1);

  if (bit == 1)
    {
      *sign = *sign | (1 << (1 - 1));
    }
  else
    {
      *sign = *sign & (~(1 << (1 - 1)));
    }

  for (int i = 14; i >= 8; i--)
    {
      bit = 0;
      bit = ((value >> (i - 1)) & 0x1);
      if (bit == 1)
        {
          *command = *command | (1 << (i - 7 - 1));
        }
      else
        {
          *command = *command & (~(1 << (i - 7 - 1)));
        }
    }

  for (int i = 7; i >= 1; i--)
    {
      bit = 0;
      bit = ((value >> (i - 1)) & 0x1);
      if (bit == 1)
        {
          *operand = *operand | (1 << (i - 1));
        }
      else
        {
          *operand = *operand & (~(1 << (i - 1)));
        }
    }

  return 0;
}