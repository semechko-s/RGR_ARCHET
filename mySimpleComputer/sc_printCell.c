#include "../include/mySimpleComputer.h"
#include "../include/myTerm.h"

void
sc_printCell (int address, enum Colors fg, enum Colors bg)
{
  if (mt_setbgcolor (bg) == -1)
    return;
  if (mt_setfgcolor (fg) == -1)
    return;
  int value;
  int sign = 0;
  int command = 0;
  int operand = 0;
  mt_gotoXY ((int)(address / 10 + 2), (address % 10) * 6 + 2);
  if (sc_memoryGet (address, &value) == 0)
    {
      sc_commandDecode (value, &sign, &command, &operand);
    }
  if (sign == 0)
    {
      printf ("+%.2x%.2x", command, operand);
    }
  else
    {
      printf ("-%.2x%.2x", command, operand);
    }
  printf ("\n");
}
