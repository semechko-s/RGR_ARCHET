#include "../include/mySimpleComputer.h"
#include "../include/myTerm.h"

void
sc_printTerm (int address, int input)
{
  int rows;
  int cols;
  mt_getscreensize (&rows, &cols);

  // mt_gotoXY((int)(rows * 2 / 3) + 1, (int)(cols * 2 / 4) + 2);
  // mt_delline();
  // printf("\n");

  // mt_delline();

  mt_gotoXY ((int)(rows * 2 / 3) + 1 + address, (int)(cols * 2 / 4) + 2);
  // printf("\n");

  int x;
  sc_memoryGet (address, &x);

  printf ("%02x%c %c%04x", address, (input == 1) ? '>' : '<',
          (x >= 0) ? '+' : '-', x);
}
