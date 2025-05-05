#include "../include/simplebasic.h"

int
sb_getGotoAddr (int gotoLine)
{
  int ln, num, addr;

  for (size_t k = 0; k < sizeof (asmString) / sizeof (asmString[0]); k++)
    {
      sscanf (asmString[k], "%d %d %d", &ln, &num, &addr);
      if (num == gotoLine)
        return addr;
    }
  return -1;
}
