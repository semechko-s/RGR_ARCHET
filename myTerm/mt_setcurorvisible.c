#include "../include/myTerm.h"

int
mt_setcursorvisible (int value)
{
  char clrscr1[] = "\E[?12;25h";
  char clrscr2[] = "\E[?25l";

  int result;
  if (value)
    {
      result = write (STDOUT_FILENO, clrscr1, sizeof (clrscr1) - 1);
      printf ("%s", clrscr1);
    }
  else
    {
      result = write (STDOUT_FILENO, clrscr2, sizeof (clrscr2) - 1);
      printf ("%s", clrscr2);
    }
  if (result != -1)
    return 0;

  else
    return -1;
}