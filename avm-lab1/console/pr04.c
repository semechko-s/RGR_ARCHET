#include <errno.h>
#include <myBigChars.h>
#include <myReadKey.h>
#include <mySimpleComputer.h>
#include <myTerm.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define READ 10
#define WRITE 11

#define LOAD 20
#define STORE 21

#define ADD 30
#define SUB 31
#define DIVIDE 32
#define MUL 33

#define JUMP 40
#define JNEG 41
#define JZ 42
#define HALT 43

#define JNS 55
#define JNP 59
#define CHL 60

int cell;
int numStrForLogs;
int term_adress[5];
int term_input[5];

int
printMemory ()
{
  if (bc_box (1, 1, 15, 61, WHITE, BLACK, "Оперативная память", RED, BLACK)
      != 0)
    {
      return -1;
    }

  for (int i = 0; i < SIZE; i++)
    {
      sc_printCell (i, WHITE, BLACK);
    }

  return 0;
}

int
printAccumulator ()
{

  if (bc_box (1, 62, 3, 25, WHITE, BLACK, "Аккумулятор", RED, BLACK) != 0)
    {
      return -1;
    }

  mt_setdefaultcolor ();

  mt_gotoXY (2, 65);
  sc_printAccumulator ();

  return 0;
}

int
printFlags ()
{
  if (bc_box (1, 87, 3, 25, WHITE, BLACK, "Регистр флагов", RED, BLACK) != 0)
    {
      return -1;
    }

  sc_printFlags (2, 92);

  return 0;
}

int
printICounter ()
{
  if (bc_box (4, 62, 3, 25, WHITE, BLACK, "Счетчик команд", RED, BLACK) != 0)
    {
      return -1;
    }

  sc_printCounters (5, 65);
  return 0;
}

int
printCommand (int address)
{

  if (bc_box (4, 87, 3, 25, WHITE, BLACK, "Команда", RED, BLACK) != 0)
    {
      return -1;
    }

  int value = 0;
  sc_memoryGet (address, &value);

  sc_printCommand (value, 5, 95);

  return 0;
}

int
printRedactedFormat (int address)
{
  if (bc_box (16, 1, 3, 61, WHITE, BLACK, "Редактируемая ячейка (формат)", RED,
              WHITE)
      != 0)
    {
      return -1;
    }

  int value = 0;
  sc_memoryGet (address, &value);
  sc_printDecodedCommand (value, 17, 2);
  mt_setdefaultcolor ();

  return 0;
}

int
printRedacted ()
{
  if (bc_box (7, 62, 12, 50, WHITE, BLACK, "Редактируемая ячейка (увеличено)",
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
  if (bc_box (19, 1, 7, 68, WHITE, BLACK, "Кеш процессора", GREEN, WHITE) != 0)
    {
      return -1;
    }

  return 0;
}

void
initCache ()
{
  cache = (CacheLine *)malloc (CACHE_SIZE * sizeof (CacheLine));
  if (cache == NULL)
    {
      return;
    }

  for (int i = 0; i < CACHE_SIZE; ++i)
    {
      cache[i].addr = -1;
      cache[i].lastAT = 0;
      for (int j = 0; j < CACHE_LINE_SIZE; j++)
        {
          cache[i].data[j] = 0;
        }
    }
}

int
cacheUI ()
{
  for (int i = 0; i < CACHE_SIZE; ++i)
    {
      mt_gotoXY (20 + i, 2);

      if (cache[i].addr == -1)
        {
          printf ("-");
        }
      else
        {
          printf ("%02d:", cache[i].addr);
          for (int j = 0; j < CACHE_LINE_SIZE; ++j)
            {
              if ((cache[i].data[j] >> 14) & 1)
                {
                  if ((cache[i].data[j] >> 13) & 1)
                    printf (" -%04X", ~(cache[i].data[j] - 1) & 0x1FFF);
                  else
                    printf ("  %04X", cache[i].data[j] & 0x1FFF);
                }
              else
                {
                  printf (" +%04X", cache[i].data[j] & 0x1FFF);
                }
            }
        }
    }
  return 0;
}

int
printHelp ()
{
  if (bc_box (19, 80, 7, 32, WHITE, BLACK, "Клавиши", GREEN, WHITE) != 0)
    {
      return -1;
    }

  char *message = "";

  mt_gotoXY (20, 81);
  message = "l - load";
  printf ("%s", message);

  mt_gotoXY (20, 81 + bc_strlen (message) + 1);
  message = "s - save";
  printf ("%s", message);

  mt_gotoXY (20, 81 + 2 * (bc_strlen (message) + 1));
  message = "i - reset";
  printf ("%s", message);

  mt_gotoXY (22, 81);
  message = "ESC - exit";
  printf ("%s", message);

  mt_gotoXY (21, 81);
  message = "r - run";
  printf ("%s", message);

  mt_gotoXY (21, 81 + bc_strlen (message) + 1);
  message = "t - step";
  printf ("%s", message);

  mt_gotoXY (23, 81);
  message = "F5 - accumulator";
  printf ("%s", message);

  mt_gotoXY (24, 81);
  message = "F6 - instruction counter";
  printf ("%s", message);

  return 0;
}

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
  printf ("%02d%c %c%02x%02x", address, (input == 1) ? '>' : '<',
          (sign == 0) ? '+' : '-', command, operand);
}

void
printInOutCells ()
{
  for (int i = 0; i < 5; i++)
    {
      mt_setdefaultcolor ();
      if (term_input[i] == -1)
        continue;
      mt_gotoXY (20 + i, 70);
      printTerm (term_adress[i], term_input[i]);
    }
}

int
printInOut ()
{
  if (bc_box (19, 69, 7, 11, WHITE, BLACK, "IN--OUT", GREEN, WHITE) != 0)
    {
      return -1;
    }

  return 0;
}

int
intToHex (int command, int operand, char *str)
{
  if (!str)
    {
      return 1;
    }

  for (int i = 0; i < 5; i++)
    {
      str[i] = 0;
    }

  int remainder;
  int whole = command;
  int i;

  for (i = 2; whole >= 16; i++)
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

  whole = operand;

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
printBigCharInBox (int address)
{
  mt_gotoXY (17, 63);
  mt_setfgcolor (GREEN);
  printf ("Номер редактируемой ячейки %.3d", cell);
  mt_setdefaultcolor ();

  int bigChars[5][2];

  int value = 0;
  sc_memoryGet (address, &value);

  int tmp_number = value;

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

  if (intToHex (command, operand, buf))
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

  int x = 63;

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
changeSizeTerm ()
{
  int size_console_x;
  int size_console_y;

  if (mt_getscreensize (&size_console_x, &size_console_y) != 0)
    {
      printf ("Error\n");
      return 1;
    }

  if (size_console_x < 115 || size_console_y < 30)
    {
      printf ("\033[8;30;115t");
    }

  mt_clrscr ();
  mt_gotoXY (1, 1);

  return 0;
}

void
initNumberCell ()
{
  cell = 0;
}

void
initNumStrForLogs ()
{
  numStrForLogs = 0;
}

void
selectCellMemory (enum way w)
{
  enum Colors color = RED;

  if (w == way_RIGHT)
    {

      mt_gotoXY ((cell / 10) + 2, (cell % 10) * 6 + 2);

      color = WHITE;
      sc_printCell (cell, WHITE, BLACK);
      color = RED;
      if (cell < SIZE - 1)
        {
          cell++;
        }
      else
        {
          cell = 0;
        }

      color = RED;
      mt_gotoXY ((cell / 10) + 2, (cell % 10) * 6 + 2);
      mt_setbgcolor (color);

      sc_printCell (cell, WHITE, RED);
      cacheUI ();
      mt_setdefaultcolor ();
      printCommand (cell);
      printRedactedFormat (cell);
      printBigCharInBox (cell);
    }

  if (w == way_LEFT)
    {
      mt_gotoXY ((cell / 10) + 2, (cell % 10) * 6 + 2);

      color = WHITE;
      sc_printCell (cell, WHITE, BLACK);
      color = RED;

      if (cell > 0)
        {
          cell--;
        }
      else
        {
          cell = SIZE - 1;
        }

      color = RED;
      mt_gotoXY ((cell / 10) + 2, (cell % 10) * 6 + 2);
      mt_setbgcolor (color);

      color = WHITE;
      sc_printCell (cell, WHITE, RED);
      cacheUI ();
      printCommand (cell);
      mt_setdefaultcolor ();
      printRedactedFormat (cell);
      printBigCharInBox (cell);
    }

  if (w == way_UP)
    {

      mt_gotoXY ((cell / 10) + 2, (cell % 10) * 6 + 2);

      color = WHITE;
      sc_printCell (cell, WHITE, BLACK);
      color = RED;

      if (cell > 9)
        {
          cell -= 10;
        }
      else if (cell == 8 || cell == 9)
        {
          cell = cell + 110;
        }
      else
        {
          cell = cell + 120;
        }

      color = RED;
      mt_gotoXY ((cell / 10) + 2, (cell % 10) * 6 + 2);

      color = WHITE;
      sc_printCell (cell, WHITE, RED);
      mt_setdefaultcolor ();
      cacheUI ();
      printCommand (cell);
      printRedactedFormat (cell);
      printBigCharInBox (cell);
    }

  if (w == way_DOWN)
    {
      mt_gotoXY ((cell / 10) + 2, (cell % 10) * 6 + 2);

      color = WHITE;
      sc_printCell (cell, WHITE, BLACK);
      color = RED;

      if (cell < SIZE - 10)
        {
          cell += 10;
        }
      else if (cell == 118 || cell == 119)
        {
          cell = cell - 110;
        }
      else
        {
          cell -= 120;
        }

      color = RED;
      mt_gotoXY ((cell / 10) + 2, (cell % 10) * 6 + 2);
      mt_setbgcolor (color);

      color = WHITE;
      sc_printCell (cell, WHITE, RED);
      mt_setdefaultcolor ();
      cacheUI ();
      printCommand (cell);
      printRedactedFormat (cell);
      printBigCharInBox (cell);
    }

  if (w == way_DEFAULT)
    {
      printBigCharInBox (cell);
      printRedactedFormat (cell);
      cacheUI ();
      color = RED;
      mt_gotoXY ((cell / 10) + 2, (cell % 10) * 6 + 2);
      mt_setbgcolor (color);
      color = WHITE;
      sc_printCell (cell, WHITE, BLACK);
      mt_setdefaultcolor ();
      printCommand (cell);
    }

  mt_setdefaultcolor ();
}

void
selectCellMemoryByNumber (int num)
{
  if (num < 0 || num > 99)
    {
      return;
    }

  cell = num;

  mt_gotoXY ((cell / 10) + 2, (cell % 10) * 6 + 2);

  enum Colors color = RED;

  mt_setbgcolor (color);

  sc_printCell (cell, WHITE, RED);
  printCommand (cell);
  printBigCharInBox (cell);
  printRedactedFormat (cell);
  printInOutCells ();

  mt_gotoXY (26, 1);
}

int
load_prog_from_file (char *path)
{
  FILE *in = fopen (path, "rb");

  if (!in)
    {
      return -1;
    }

  if (fread (memory, sizeof (int), 128, in) == 0)
    {
      fprintf (stderr, "Error reading from file\n");
      fclose (in);
      return -1;
    }

  fread (&accumulator, sizeof (int), 1, in);

  int value = 0;

  fread (&value, sizeof (int), 1, in);
  sc_regSet (FLAG_OVERSTEP_MEMORY, value);
  fread (&value, sizeof (int), 1, in);
  sc_regSet (FLAG_OVERFLOW_OPERATION, value);
  fread (&value, sizeof (int), 1, in);
  sc_regSet (FLAG_INVALID_COMMAND, value);
  fread (&value, sizeof (int), 1, in);
  sc_regSet (FLAG_DIVIDE_BY_ZERO, value);
  fread (&value, sizeof (int), 1, in);
  sc_regSet (FLAG_CLOCK_PULSE, value);

  fread (&icounter, sizeof (int), 1, in);

  fclose (in);

  return 0;
}

int
save_prog_in_file (char *path)
{
  FILE *out = fopen (path, "wb");

  if (!out)
    {
      return -1;
    }

  if (fwrite (memory, sizeof (int), 128, out) == 0)
    {
      fprintf (stderr, "Error reading from file\n");
      fclose (out);
      return -1;
    }

  fwrite (&accumulator, sizeof (int), 1, out);

  int value = 0;

  fwrite (&value, sizeof (int), 1, out);
  sc_regSet (FLAG_OVERSTEP_MEMORY, value);
  fwrite (&value, sizeof (int), 1, out);
  sc_regSet (FLAG_OVERFLOW_OPERATION, value);
  fwrite (&value, sizeof (int), 1, out);
  sc_regSet (FLAG_INVALID_COMMAND, value);
  fwrite (&value, sizeof (int), 1, out);
  sc_regSet (FLAG_DIVIDE_BY_ZERO, value);
  fwrite (&value, sizeof (int), 1, out);
  sc_regSet (FLAG_CLOCK_PULSE, value);

  fwrite (&icounter, sizeof (int), 1, out);

  fflush (out);

  fclose (out);

  return 0;
}

void
incrementNumStrForLogs ()
{
  numStrForLogs++;
  if (numStrForLogs > 10)
    {
      mt_gotoXY (26, 1);
      for (int i = 26; i < 36; i++)
        {
          printf ("                     \n");
        }
      numStrForLogs = 0;
    }
}

int
interface (int size, int mem, int acc, int insCoun, int oper, int fl, int bc,
           int rd, int h, int ch, int bcib, int io)
{
  if (size)
    {
      changeSizeTerm ();
    }

  if (mem)
    {
      if (printMemory () != 0)
        {
          return 1;
        }
      selectCellMemoryByNumber (cell);
    }

  if (acc)
    {
      if (printAccumulator () != 0)
        {
          return 1;
        }
    }

  if (insCoun)
    {
      if (printICounter () != 0)
        {
          return 1;
        }
    }

  if (oper)
    {
      if (printCommand (cell) != 0)
        {
          return 1;
        }
    }

  if (fl)
    {
      if (printFlags () != 0)
        {
          return 1;
        }
    }

  if (bc)
    {
      if (printRedacted () != 0)
        {
          return 1;
        }
    }

  if (rd)
    {
      if (printRedactedFormat (cell) != 0)
        {
          return 1;
        }
    }

  if (h)
    {
      if (printHelp () != 0)
        {
          return 1;
        }
    }
  if (ch)
    {
      if (printCache () != 0)
        {
          return 1;
        }
      cacheUI ();
      printf ("\n");
    }

  if (bcib)
    {
      if (printBigCharInBox (cell) != 0)
        {
          return 1;
        }
    }

  if (io)
    {
      if (printInOut () != 0)
        {
          return 1;
        }
      printInOutCells ();
      printf ("\n");
    }

  mt_gotoXY (26, 1);

  return 0;
}

int
ALU (int command, int operand)
{
  if (operand > 127)
    {
      return 1;
    }

  switch (command)
    {
    case ADD:
      {
        int temp = 0;
        sc_accumulatorGet (&temp);
        if ((temp + memory[operand]) >= 65535)
          {
            sc_regSet (FLAG_OVERFLOW_OPERATION, 1);
            break;
          }
        sc_accumulatorSet (temp + memory[operand]);
        sc_icounterSet (cell);
        break;
      }
    case SUB:
      {
        if ((accumulator - memory[operand]) < -65534)
          {
            sc_regSet (FLAG_OVERFLOW_OPERATION, 1);
            break;
          }
        sc_accumulatorSet (accumulator - memory[operand]);
        sc_icounterSet (cell);
        break;
      }
    case DIVIDE:
      {
        if (memory[operand] == 0 || accumulator == 0)
          {
            sc_regSet (FLAG_DIVIDE_BY_ZERO, 1);
            break;
          }
        sc_accumulatorSet (accumulator / memory[operand]);
        sc_icounterSet (cell);
        break;
      }
    case MUL:
      {
        if ((accumulator * memory[operand]) >= 65535)
          {
            sc_regSet (FLAG_OVERFLOW_OPERATION, 1);
            break;
          }
        sc_accumulatorSet (accumulator * memory[operand]);
        sc_icounterSet (cell);
        break;
      }
    default:
      return 1;
    }
  fflush (stdout);
  return 0;
}

int
CU ()
{
  int command = 0;
  int operand = 0;
  int sign = 0;

  // raise(SIGALRM);

  if (sc_commandDecode (memory[cell], &sign, &command, &operand) != 0)
    {
      sc_regSet (FLAG_INVALID_COMMAND, 1);
      return 1;
    }

  if (sign)
    {
      return 1;
    }

  if (command > 33 || command < 30)
    {
      switch (command)
        {
        case READ:
          {
            int tmp = 0;
            printInOut ();
            mt_gotoXY (20 + numStrForLogs, 70);
            printf ("%.2d<", operand);
            rk_readValue (&memory[operand], 1);

            printf ("\n");
            if (tmp > 65535)
              {
                sc_regSet (FLAG_OVERFLOW_OPERATION, 1);
                break;
              }
            addTerm (operand, 0);
            sc_icounterSet (cell);

            break;
          }
        case WRITE:
          {
            mt_gotoXY (20 + numStrForLogs, 70);
            addTerm (operand, 1);
            sc_icounterSet (cell);

            break;
          }
        case LOAD:
          {
            sc_accumulatorSet (memory[operand]);
            sc_icounterSet (cell);
            break;
          }
        case STORE:
          {
            sc_accumulatorGet (&memory[operand]);
            sc_icounterSet (cell);
            break;
          }
        case CHL:
          {
            sc_accumulatorSet ((int)memory[operand] << 1);
            sc_icounterSet (cell);
            break;
          }
        case JNP:
          {
            int val;
            sc_accumulatorGet (&val);
            if (ALU (command, operand) % 2 != 0)
              {
                cell = operand;
              }
            cell = operand;
            sc_icounterSet (cell);
            break;
          }
        case JUMP:
          {
            cell = operand;
            break;
          }
        case JNEG:
          {
            int temp;
            sc_accumulatorGet (&temp);

            if (temp < 0)
              {
                cell = operand;
              }
            break;
          }
        case JZ:
          {
            int temp;
            sc_accumulatorGet (&temp);

            if (temp == 0)
              {
                cell = operand;
              }
            break;
          }
        case JNS:
          {
            int temp;
            sc_accumulatorGet (&temp);

            if (temp > 0)
              {
                cell = operand;
              }
            break;
          }

        case HALT:
          sc_icounterSet (cell);
          return 2;
          break;
        }
    }
  else
    {
      if (ALU (command, operand))
        {
          return 1;
        }
    }
  return 0;
}

void
test ()
{
  sc_commandEncode (0, 10, 78,
                    &memory[0]); // READ 78 ( 78- IN-OUT)
  sc_commandEncode (0, 10, 88,
                    &memory[1]); // READ 88 ( 88- IN-OUT)

  sc_commandEncode (0, 20, 79, &memory[2]); // LOAD 79
  sc_commandEncode (0, 30, 89, &memory[3]); // ADD 89
  sc_commandEncode (0, 21, 99, &memory[4]); // STORE 99

  sc_commandEncode (0, 20, 78, &memory[5]); // LOAD 78
  sc_commandEncode (0, 30, 88, &memory[6]); // ADD 88
  sc_commandEncode (0, 21, 98, &memory[7]); // STORE 98

  sc_commandEncode (0, 43, 0, &memory[9]); // HALT

  sc_commandEncode (0, 11, 8, &memory[8]); // WRITE

  sc_commandEncode (0, 30, 109, &memory[10]); // ADD 30 to accum

  sc_commandEncode (0, 60, 0, &memory[11]); // CHL 1 (1)
  sc_commandEncode (0, 59, 2, &memory[12]); // JNP 2
}

void
IRC (int signum)
{
  switch (signum)
    {
    case SIGALRM:

      if (ticks < 9999)
        {
          ticks++;
        }
      else
        {
          ticks = 0;
        }
      break;

    case SIGUSR1:
      alarm (0);
      ticks = 0;
      cell = 0;
      rk_mytermsave ();
      sc_icounterInit ();
      sc_memoryInit ();
      initCache ();
      updateStatic = true;
      accumulator &= (1 << 14);
      sc_regInit ();
      sc_regSet (FLAG_CLOCK_PULSE, 1);
      // interface(0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
      break;
    default:
      break;
    }
}

int
runtime ()
{
  int statusIter = 0;

  do
    {
      sc_regSet (FLAG_CLOCK_PULSE, 1);
      raise (SIGALRM);
      statusIter = CU ();
      mt_setdefaultcolor ();
      interface (0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);

      sleep (1);
      if (statusIter == 1)
        {
          printf ("Status Iteration = 1 ( Error )\n");
          break;
        }
      cell++;
    }
  while (statusIter != 2);

  mt_gotoXY (26, 1);
  printf ("End program\n");
  return 0;
}

int
main ()
{
  mt_clrscr ();

  sc_memoryInit ();
  sc_regInit ();
  sc_icounterInit ();
  initNumberCell ();
  sc_icounterInit ();
  initCache ();
  initNumStrForLogs ();
  termInit ();

  sc_regSet (FLAG_CLOCK_PULSE, 1);

  enum keys key;
  enum way w;
  w = way_DEFAULT;
  selectCellMemory (w);

  test ();

  signal (SIGALRM, IRC);
  signal (SIGUSR1, IRC);

  interface (1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);

  while (1)
    {
      rk_readkey (&key);
      if (key == ESC)
        {
          break;
        }
      if (key == UP)
        {
          w = way_UP;
          selectCellMemory (w);
          continue;
        }
      if (key == LEFT)
        {
          w = way_LEFT;
          selectCellMemory (w);
          continue;
        }
      if (key == DOWN)
        {
          w = way_DOWN;
          selectCellMemory (w);
          continue;
        }
      if (key == RIGHT)
        {
          w = way_RIGHT;
          selectCellMemory (w);
          continue;
        }
      if (key == F5)
        {
          accumulator = memory[cell];
          interface (0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
          continue;
        }
      if (key == F6)
        {
          sc_icounterSet (cell);
          interface (0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0);
          continue;
        }
      if (key == ENTER)
        {
          printInOut ();
          mt_gotoXY ((cell / 10) + 2, (cell % 10) * 6 + 2);
          printf ("     ");
          mt_gotoXY ((cell / 10) + 2, (cell % 10) * 6 + 2);
          rk_readValue (&memory[cell], 1);
          addTerm (cell, 0);
          interface (1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
          continue;
        }
      if (key == 'i')
        {
          sc_regInit ();
          sc_memoryInit ();
          initCache ();
          cell = 0;
          interface (0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0);
          selectCellMemoryByNumber (cell);
          raise (SIGUSR1);
          continue;
        }
      if (key == 'l')
        {
          rk_mytermsave ();
          rk_mytermregime (0, 1, 1, 1, 1);
          mt_gotoXY (26 + numStrForLogs, 1);
          printf ("Enter path to file: ");
          char *path = calloc (0, sizeof (char) * 128);
          scanf ("%s", path);
          mt_gotoXY (26, 1);
          printf ("                                               ");
          load_prog_from_file (path);
          interface (0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
          rk_mytermrestore ();
          continue;
        }
      if (key == 's')
        {
          mt_gotoXY (26 + numStrForLogs, 1);
          printf ("Enter path to file: ");
          char *path = calloc (0, sizeof (char) * 30);
          scanf ("%s", path);
          mt_gotoXY (26, 1);
          printf ("                                               ");
          save_prog_in_file (path);
          interface (0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0);
          continue;
        }
      if (key == 'r')
        {
          sc_regSet (FLAG_CLOCK_PULSE, 0);
          rk_mytermsave ();
          rk_mytermregime (0, 0, 1, 1, 1);
          runtime ();
          rk_mytermrestore ();
          sc_regSet (FLAG_CLOCK_PULSE, 1);
          continue;
        }
      if (key == 't')
        {
          sc_regSet (FLAG_CLOCK_PULSE, 0);
          CU ();
          sc_regSet (FLAG_CLOCK_PULSE, 1);
          fflush (stdout);
          interface (1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
          continue;
        }
    }

  int rows, cols;
  mt_getscreensize (&rows, &cols);

  mt_gotoXY (rows, 1);
  return 0;
}
