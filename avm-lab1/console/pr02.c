#include "../include/mySimpleComputer.h"
#include "../include/myTerm.h"
#include <stdio.h>
#include <unistd.h>

void
printTables (int cols)
{

  for (int i = 1; i <= cols; i++)
    {
      // memory
      if (i < (cols / 2) - 2)
        {
          mt_gotoXY (1, i);
          printf ("-\n");
        }

      // accumulator
      if (i >= (cols / 2) && i <= (cols / 2) + (cols / 4))
        {
          mt_gotoXY (1, i);
          printf ("-\n");
        }

      // flags
      if (i >= (cols / 2) + (cols / 4) + 2 && i <= cols)
        {
          mt_gotoXY (1, i);
          printf ("-\n");
        }

      // count commands
      if (i >= (cols / 2) && i <= (cols / 2) + (cols / 4))
        {
          mt_gotoXY (5, i);
          printf ("-\n");
        }

      // command
      if (i >= (cols / 2) + (cols / 4) + 2 && i <= cols)
        {
          mt_gotoXY (5, i);
          printf ("-\n");
        }

      if (i < (cols / 2) - 2)
        {
          mt_gotoXY (16, i);
          printf ("-\n");
        }
    }

  for (int i = 1; i <= cols; i++)
    {

      if (i == (cols / 4) - 3)
        {
          mt_gotoXY (1, i);
          printf ("RAM\n");
        }

      if (i == (cols / 2) + (cols / 10))
        {
          mt_gotoXY (1, i);
          printf ("Accumulator\n");
        }

      if (i == (cols / 2) + (cols / 3) + 4)
        {
          mt_gotoXY (1, i);
          printf ("Flags\n");
        }

      if (i == (cols / 2) + (cols / 10))
        {
          mt_gotoXY (5, i);
          printf ("Count commands\n");
        }

      if (i == (cols / 2) + (cols / 3) + 4)
        {
          mt_gotoXY (5, i);
          printf ("Command\n");
        }

      if (i == (cols / 4) - 8)
        {
          mt_gotoXY (16, i);
          printf ("Editing cell\n");
        }
    }
}

int
main ()
{
  mt_clrscr ();

  sc_memoryInit ();
  sc_memorySet (0, 32767);
  sc_memorySet (1, 32766);
  sc_memorySet (6, 32700);

  sc_regInit ();

  int rows = 0, cols = 0;

  mt_getscreensize (&rows, &cols);

  printTables (cols);
  printf ("\n");

  for (int i = 0; i < SIZE; i++)
    {
      sc_printCell (i, GREEN, BLACK);
      printf ("\n");
    }
  mt_setdefaultcolor ();

  sc_regSet (FLAG_OVERSTEP_MEMORY, 1);

  int sign = 0;
  int command = 21;
  int operand = 100;
  int value = 0;
  sc_commandEncode (sign, command, operand, &value);

  sc_accumulatorSet (32767);
  sc_printAccumulator ();
  printf ("\n");

  sc_printFlags (2, (cols / 2) + (cols / 4) + 2);
  printf ("\n");

  sc_printCounters (6, (cols / 2));
  printf ("\n");

  sc_printCommand (value, 6, (cols / 2) + (cols / 4) + 2);
  printf ("\n");

  int y;
  sc_memoryGet (0, &y);

  sc_printDecodedCommand (y, 17, 0);
  printf ("\n");

  for (int i = 0; i < 7; i++)
    {
      // printDecodedCommand(value);
      sc_printTerm (i, 0);
      sleep (1);
      printf ("\n");
    }

  mt_gotoXY (rows, 0);

  mt_setdefaultcolor ();
}