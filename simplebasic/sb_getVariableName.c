#include "../include/simplebasic.h"
char
sb_getVarName (int varAddr, int offset)
{
  if ((varAddr - offset >= 0)
      && (strcmp ((variables + varAddr - offset), "\0") != 0))
    {
      return variables[varAddr - offset];
    }
  else
    {
      return '\0';
    }
}