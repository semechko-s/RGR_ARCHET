#include "../include/mySimpleComputer.h"

int
sc_memoryInit ()
{
  for (int i = 0; i < SIZE; i++)
    {
      memory[i] = 0;
    }
  return 0;
}