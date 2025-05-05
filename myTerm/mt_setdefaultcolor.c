#include "../include/myTerm.h"

int
mt_setdefaultcolor (void)
{
  char clrscr[] = "\E[0m";

  int result = write (STDOUT_FILENO, clrscr, sizeof (clrscr) - 1);
  if (result != -1)
    {
      printf ("%s", clrscr);
      return 0;
    }
  else
    return -1;
}