#include "../include/myBigChars.h"
#include "../include/mySimpleComputer.h"
#include "../include/myTerm.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int
printMemory ()
{
  if (bc_box (1, 1, 15, 63, WHITE, BLACK, "Оперативная память", RED, BLACK)
      != 0)
    {
      return -1;
    }

  for (int i = 0; i < SIZE; i++)
    {
      sc_memorySet (i, rand () % 32767);
    }

  sc_memorySet (0, 32767);
  sc_printCell (0, BLACK, WHITE);

  for (int i = 1; i < SIZE; i++)
    {
      sc_printCell (i, WHITE, BLACK);
    }

  return 0;
}

int
printAccumulator ()
{

  if (bc_box (1, 64, 3, 30, WHITE, BLACK, "Аккумулятор", RED, BLACK) != 0)
    {
      return -1;
    }

  int value = 0;
  sc_accumulatorGet (&value);

  int sign = 0, command = 0, operand = 0;
  sc_commandDecode (value, &sign, &command, &operand);

  mt_gotoXY (2, 70);
  printf ("sc: %c%02x%02x hex: %04x", (sign == 0) ? '+' : '-', command,
          operand, value);

  return 0;
}

int
printFlags ()
{
  if (bc_box (1, 95, 3, 30, WHITE, BLACK, "Регистр флагов", RED, BLACK) != 0)
    {
      return -1;
    }

  sc_regSet (FLAG_OVERFLOW_OPERATION, 1);
  sc_regSet (FLAG_CLOCK_PULSE, 1);
  sc_regSet (FLAG_INVALID_COMMAND, 1);

  sc_printFlags (2, 105);

  return 0;
}

int
printICounter ()
{
  if (bc_box (4, 64, 3, 30, WHITE, BLACK, "Счетчик команд", RED, BLACK) != 0)
    {
      return -1;
    }

  sc_printCounters (5, 74);
  return 0;
}

int
printCommand ()
{

  if (bc_box (4, 95, 3, 30, WHITE, BLACK, "Команда", RED, BLACK) != 0)
    {
      return -1;
    }

  int value = 0;
  sc_memoryGet (0, &value);

  sc_printCommand (value, 5, 105);

  return 0;
}

int
printRedactedFormat ()
{
  if (bc_box (16, 1, 3, 63, WHITE, BLACK, "Редактируемая ячейка (формат)", RED,
              WHITE)
      != 0)
    {
      return -1;
    }

  int value = 0;
  sc_memoryGet (0, &value);
  sc_printDecodedCommand (value, 17, 3);

  return 0;
}

int
printRedacted ()
{
  if (bc_box (7, 64, 12, 61, WHITE, BLACK, "Редактируемая ячейка (увеличено)",
              RED, WHITE)
      != 0)
    {
      return -1;
    }

  return 0;
}

int
printCache ()
{
  if (bc_box (19, 1, 7, 72, WHITE, BLACK, "Кеш процессора", GREEN, WHITE) != 0)
    {
      return -1;
    }

  return 0;
}

int
printInOut ()
{
  if (bc_box (19, 73, 7, 11, WHITE, BLACK, "IN--OUT", GREEN, WHITE) != 0)
    {
      return -1;
    }

  return 0;
}

int
printHelp ()
{
  if (bc_box (19, 84, 7, 41, WHITE, BLACK, "Клавиши", GREEN, WHITE) != 0)
    {
      return -1;
    }
  return 0;
}

int term_adress[5];
int term_input[5];

int
msleep (long msec)
{
  struct timespec ts;
  int res;

  if (msec < 0)
    {
      errno = EINVAL;
      return -1;
    }

  ts.tv_sec = msec / 1000;
  ts.tv_nsec = (msec % 1000) * 1000000;

  do
    {
      res = nanosleep (&ts, &ts);
    }
  while (res && errno == EINTR);

  return res;
}

void
addTerm (int address, int input)
{
  for (int i = 0; i < 4; i++)
    {
      term_adress[i] = term_adress[i + 1];
      term_input[i] = term_input[i + 1];
    }

  term_adress[4] = address;
  term_input[4] = input;
}

void
termInit ()
{
  for (int i = 0; i < 6; i++)
    {
      term_input[i] = -1;
      term_adress[i] = 10;
    }
}

void
printTerm (int address, int input)
{
  int value = 0;
  sc_memoryGet (address, &value);
  int sign = 0, command = 0, operand = 0;
  sc_commandDecode (value, &sign, &command, &operand);
  printf ("%02x%c %c%04x", address, (input == 1) ? '>' : '<',
          (sign == 0) ? '+' : '-', value);
}

void
printInOutCells ()
{
  for (int i = 0; i < 5; i++)
    {
      if (term_input[i] == -1)
        continue;
      mt_gotoXY (20 + i, 74);
      printTerm (term_adress[i], term_input[i]);
    }
  fflush (stdout);
  msleep (500);
}

int
intToHex (int number, char *str)
{
  if (!str || number >= 65535 || number < 0)
    {
      return 1;
    }

  for (int i = 0; i < 5; i++)
    {
      str[i] = 0;
    }

  int remainder;
  int whole = number;
  int i;

  for (i = 0; whole >= 16; i++)
    {
      remainder = whole % 16;
      whole = whole / 16;
      if (remainder == 10)
        {
          str[i] = 'A';
        }
      else if (remainder == 11)
        {
          str[i] = 'B';
        }
      else if (remainder == 12)
        {
          str[i] = 'C';
        }
      else if (remainder == 13)
        {
          str[i] = 'D';
        }
      else if (remainder == 14)
        {
          str[i] = 'E';
        }
      else if (remainder == 15)
        {
          str[i] = 'F';
        }
      else
        {
          str[i] = remainder + 48;
        }
    }

  if (whole != 0)
    {
      if (whole == 10)
        {
          str[i] = 'A';
        }
      else if (whole == 11)
        {
          str[i] = 'B';
        }
      else if (whole == 12)
        {
          str[i] = 'C';
        }
      else if (whole == 13)
        {
          str[i] = 'D';
        }
      else if (whole == 14)
        {
          str[i] = 'E';
        }
      else if (whole == 15)
        {
          str[i] = 'F';
        }
      else
        {
          str[i] = whole + 48;
        }
    }

  return 0;
}

int
printBigCharInBox ()
{
  int bigChars[5][2];

  int tmp_number = memory[0];

  int sign = 0, command = 0, operand = 0;
  sc_commandDecode (tmp_number, &sign, &command, &operand);

  if (sign == 0)
    {
      bigChars[0][0] = bc_Plus (0);
      bigChars[0][1] = bc_Plus (1);
    }
  else
    {
      bigChars[0][0] = bc_Minus (0);
      bigChars[0][1] = bc_Minus (1);
    }

  char buf[5];

  if (intToHex (tmp_number, buf))
    {
      return 1;
    }

  int j = 4;

  for (int i = 0; i < 4; i++)
    {
      if (buf[i] == '0')
        {
          fflush (stdout);
          bigChars[j][0] = bc_Null (0);
          bigChars[j][1] = bc_Null (1);
        }
      else if (buf[i] == '1')
        {
          bigChars[j][0] = bc_One (0);
          bigChars[j][1] = bc_One (1);
        }
      else if (buf[i] == '2')
        {
          bigChars[j][0] = bc_Two (0);
          bigChars[j][1] = bc_Two (1);
        }
      else if (buf[i] == '3')
        {
          bigChars[j][0] = bc_Three (0);
          bigChars[j][1] = bc_Three (1);
        }
      else if (buf[i] == '4')
        {
          bigChars[j][0] = bc_Four (0);
          bigChars[j][1] = bc_Four (1);
        }
      else if (buf[i] == '5')
        {
          bigChars[j][0] = bc_Five (0);
          bigChars[j][1] = bc_Five (1);
        }
      else if (buf[i] == '6')
        {
          bigChars[j][0] = bc_Six (0);
          bigChars[j][1] = bc_Six (1);
        }
      else if (buf[i] == '7')
        {
          bigChars[j][0] = bc_Seven (0);
          bigChars[j][1] = bc_Seven (1);
        }
      else if (buf[i] == '8')
        {
          bigChars[j][0] = bc_Eight (0);
          bigChars[j][1] = bc_Eight (1);
        }
      else if (buf[i] == '9')
        {
          bigChars[j][0] = bc_Nine (0);
          bigChars[j][1] = bc_Nine (1);
        }
      else if (buf[i] == 'A')
        {
          bigChars[j][0] = bc_A (0);
          bigChars[j][1] = bc_A (1);
        }
      else if (buf[i] == 'B')
        {
          bigChars[j][0] = bc_B (0);
          bigChars[j][1] = bc_B (1);
        }
      else if (buf[i] == 'C')
        {
          bigChars[j][0] = bc_C (0);
          bigChars[j][1] = bc_C (1);
        }
      else if (buf[i] == 'D')
        {
          bigChars[j][0] = bc_D (0);
          bigChars[j][1] = bc_D (1);
        }
      else if (buf[i] == 'E')
        {
          bigChars[j][0] = bc_E (0);
          bigChars[j][1] = bc_E (1);
        }
      else if (buf[i] == 'F')
        {
          bigChars[j][0] = bc_F (0);
          bigChars[j][1] = bc_F (1);
        }
      else
        {
          bigChars[j][0] = bc_Null (0);
          bigChars[j][1] = bc_Null (1);
        }
      j--;
    }

  int x = 70;

  for (int i = 0; i < 5; i++)
    {
      bc_printbigchar (bigChars[i], x + i * 10, 9, YELLOW, BLACK);
    }

  mt_gotoXY (26, 1);
  mt_setdefaultcolor ();
  printf ("\n");
  return 0;
}

int
main ()
{
  sc_memoryInit ();
  sc_regInit ();
  sc_accumulatorInit ();
  sc_icounterInit ();

  mt_clrscr ();

  int rows = 0, cols = 0;

  mt_getscreensize (&rows, &cols);

  printMemory ();
  printAccumulator ();
  printFlags ();
  printICounter ();
  printCommand ();

  printRedactedFormat ();
  printRedacted ();
  printCache ();
  printInOut ();
  printHelp ();
  printBigCharInBox ();
  termInit ();

  while (1)
    {
      printInOutCells ();
      addTerm (rand () % 30, 1);
    }

  mt_setdefaultcolor ();
  printf ("\n");
  mt_gotoXY (rows, 1);

  return 0;
}