#include "../include/myTerm.h"

int
mt_getscreensize (int *rows, int *cols)
{
  struct winsize ws;
  if (!ioctl (STDOUT_FILENO, TIOCGWINSZ, &ws))
    {
      *rows = ws.ws_row;
      *cols = ws.ws_col;
      // printf("row = %d\ncol = %d", *rows, *cols);
      return 0;
    }
  else
    return -1;
}