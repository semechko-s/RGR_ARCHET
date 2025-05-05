#include "../include/mySimpleComputer.h"
#include "../include/myTerm.h"

void
sc_printAccumulator (void)
{
  int x;
  sc_accumulatorGet (&x);

  int sign = 0, command = 0, operand = 0;

  sc_commandDecode (x, &sign, &command, &operand);

  if (sign)
    {
      printf ("sc: -%.2x%.2x hex: %.4x", command, operand, x);
    }
  else
    {
      printf ("sc: +%.2x%.2x hex: %.4x", command, operand, x);
    }
  printf ("\n");
}