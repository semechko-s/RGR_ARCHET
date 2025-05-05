#include "../include/mySimpleComputer.h"

int
sc_memoryGet (int address, int *value)
{
  if ((address < 0) || (address > SIZE))
    {
      printf ("Going beyond memory limits\n");
      sc_regSet (FLAG_OVERSTEP_MEMORY, 1);
      return -1;
    }
  if (!value)
    {
      printf ("Empty pointer\n");
      return -1;
    }
  int index;
  int newAddr = address;
  newAddr = newAddr / 10 * 10;
  sc_updateCacheAfterSave (address, newAddr, &index);
  *value = memory[address];
  return 0;
}