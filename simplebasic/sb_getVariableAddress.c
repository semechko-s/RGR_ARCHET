#include "../include/simplebasic.h"

int
sb_getVarAddr (char varName, int offset)
{
  size_t i;
  for (i = 0; i < sizeof (variables); i++)
    {
      if (variables[i] == varName)
        return offset + i;

      else if (strcmp ((variables + i), "\0") == 0)
        break;
    }
  *(variables + i) = varName;
  return offset + i;
}