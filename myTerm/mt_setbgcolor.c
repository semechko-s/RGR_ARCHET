#include "../include/myTerm.h"

int
mt_setbgcolor (enum Colors color)
{
  char clrscr[7];
  sprintf (clrscr, "\E[4%dm", color);

  int result = write (STDOUT_FILENO, clrscr, sizeof (clrscr) - 1);

  if (result != -1)
    {
      printf ("%s", clrscr);
      return 0;
    }
  else
    return -1;
}