#include <stdio.h>
#include <stdlib.h>

#include "../include/mySimpleComputer.h"

void
printCell (int address)
{
  int value;
  if (sc_memoryGet (address, &value) == 0)
    {
      int sign = 0;
      int command = 0;
      int operand = 0;
      sc_commandDecode (value, &sign, &command, &operand);
      // printf("%d: %d_%d_%d ", address, sign, command, operand);
    }
  printf ("%x ", value);
}

void
printFlags ()
{
  int value;
  sc_regGet (FLAG_OVERFLOW_OPERATION, &value);
  printf ("%c ", value ? 'O' : '_');
  sc_regGet (FLAG_DIVIDE_BY_ZERO, &value);
  printf ("%c ", value ? 'Z' : '_');
  sc_regGet (FLAG_OVERSTEP_MEMORY, &value);
  printf ("%c ", value ? 'M' : '_');
  sc_regGet (FLAG_CLOCK_PULSE, &value);
  printf ("%c ", value ? 'P' : '_');
  sc_regGet (FLAG_INVALID_COMMAND, &value);
  printf ("%c ", value ? 'C' : '_');
}

void
printDecodedCommand (int value)
{
  printf ("Dec: %d  ", value);
  printf ("Oct: %o  ", value);
  printf ("Hex: %X  ", value);
  printf ("Bin: ");
  for (int i = 15; i >= 1; i--)
    {
      printf ("%d", (value >> (i - 1)) & 0x1);
    }
  printf ("\n");
}

void
printAccumulator ()
{
  int value;
  sc_accumulatorGet (&value);
  printf ("Accumulator: %d\n", value);
}

void
printIcounter ()
{
  int value;
  sc_icounterGet (&value);
  printf ("Icounter: %d\n", value);
}

int
main ()
{
  sc_memoryInit ();
  sc_accumulatorInit ();
  sc_icounterInit ();
  sc_regInit ();

  for (int i = 0; i < SIZE; i++)
    {
      sc_memorySet (i, i * 10);
    }

  for (int i = 0; i < SIZE; i++)
    {
      printCell (i);
      if ((i + 1) % 10 == 0)
        {
          printf ("\n");
        }
    }

  printf ("\n");

  sc_memorySet (200, 5000);

  sc_regSet (FLAG_OVERSTEP_MEMORY, 1);
  sc_regSet (FLAG_DIVIDE_BY_ZERO, 0);
  printFlags ();

  sc_regSet (10, 1);

  sc_accumulatorSet (123);
  printAccumulator ();

  sc_accumulatorSet (9999);

  sc_icounterSet (50);
  printIcounter ();

  sc_icounterSet (-5);

  int memory_value;
  sc_memoryGet (5, &memory_value);
  printDecodedCommand (memory_value);
  printf ("\n");
  printDecodedCommand (123);

  int command = 512;
  printDecodedCommand (command);
  printAccumulator ();

  int encodedCommand;
  sc_commandEncode (1, 0x10, 0x0F, &encodedCommand);
  printDecodedCommand (encodedCommand);

  system ("PAUSE");

  return 0;
}