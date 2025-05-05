#include "../include/mySimpleComputer.h"
#include "../include/myTerm.h"

void
sc_printCommand (int value, int x, int y)
{
  mt_gotoXY (x, y);
  int sign = 0;
  int command = 0;
  int operand = 0;
  if (sc_commandDecode (value, &sign, &command, &operand) != -1)
    {
      if (sign == 0)
        printf ("+ %.2d : %.2d", command, operand);
      else
        printf ("- %.2d : %.2d", command, operand);
    }
}