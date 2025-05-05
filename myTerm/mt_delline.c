#include "../include/myTerm.h"

int
mt_delline (void)
{
  char clrscr[] = "\033[M";

  int result = write (STDOUT_FILENO, clrscr, sizeof (clrscr) - 1);
  if (result != -1)
    {
      printf ("%s", clrscr);
      return 0;
    }
  else
    return -1;
}