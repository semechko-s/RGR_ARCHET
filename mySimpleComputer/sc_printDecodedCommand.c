#include "../include/mySimpleComputer.h"
#include "../include/myTerm.h"

void
sc_printDecodedCommand (int value, int x, int y)
{

  mt_gotoXY (x, y);

  printf ("dec: %d | oct: %o | hex: %x   bin: ", value, value, value);
  for (int i = 15; i >= 1; i--)
    {
      printf ("%d", (value >> (i - 1)) & 0x1);
    }
}