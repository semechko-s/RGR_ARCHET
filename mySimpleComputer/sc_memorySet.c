#include "../include/mySimpleComputer.h"

int
sc_memorySet (int address, int value)
{
  if ((address < 0) || (address >= SIZE) || (value < 0) || (value > 32767))
    {
      printf ("Going beyond memory limit\n");
      sc_regSet (FLAG_OVERSTEP_MEMORY, 1);
      return -1;
    }
  int index;
  int newAddr = address;
  newAddr = newAddr / 10 * 10;
  sc_updateCacheAfterSave (address, newAddr, &index);
  memory[address] = value;
  return 0;
}