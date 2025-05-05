#include "../include/mySimpleComputer.h"
#include "../include/myTerm.h"

void
sc_printFlags (int x, int y)
{
  mt_setdefaultcolor ();
  printf ("\n");
  mt_gotoXY (x, y);

  int value;
  sc_regGet (FLAG_OVERFLOW_OPERATION, &value);
  printf ("%c  ", value ? 'P' : '_');
  sc_regGet (FLAG_DIVIDE_BY_ZERO, &value);
  printf ("%c  ", value ? '0' : '_');
  sc_regGet (FLAG_OVERSTEP_MEMORY, &value);
  printf ("%c  ", value ? 'M' : '_');
  sc_regGet (FLAG_CLOCK_PULSE, &value);
  printf ("%c  ", value ? 'T' : '_');
  sc_regGet (FLAG_INVALID_COMMAND, &value);
  printf ("%c  ", value ? 'E' : '_');
}