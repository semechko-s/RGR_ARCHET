#include "../include/mySimpleComputer.h"

int
sc_icounterSet (int value)
{
  if ((value < 0) || (value > 32767))
    {
      printf ("Invalid value\n");
      return -1;
    }
  icounter = value;
  return 0;
}