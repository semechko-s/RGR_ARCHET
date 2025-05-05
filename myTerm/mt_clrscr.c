#include "../include/myTerm.h"

int
mt_clrscr (void)
{
  char clrscr[] = "\033[H\033[J";
  int result = write (STDOUT_FILENO, clrscr, sizeof (clrscr) - 1);
  // close (fd);
  if (result != -1)
    return 0;
  else
    return -1;
}