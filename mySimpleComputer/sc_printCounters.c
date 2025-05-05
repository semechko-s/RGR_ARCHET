#include "../include/mySimpleComputer.h"
#include "../include/myTerm.h"

void
sc_printCounters (int x, int y)
{
  mt_gotoXY (x, y);

  int fl;
  sc_regGet (FLAG_CLOCK_PULSE, &fl);
  int value;
  sc_icounterGet (&value);
  printf ("T: %02d    IC: %c%04x", ticks, (value >= 0 ? '+' : '-'), value);
  printf ("\n");
}