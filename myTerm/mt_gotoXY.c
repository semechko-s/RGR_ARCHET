#include "../include/myTerm.h"

int
mt_gotoXY (int rows, int cols)
{
  int rowsMax = 0, colsMax = 0;
  char xy[9];

  mt_getscreensize (&rowsMax, &colsMax);

  if ((rows > 0) && (cols > 0) && (rows <= rowsMax) && (cols <= colsMax))
    {
      sprintf (xy, "\033[%d;%dH", rows, cols);
      // write(STDOUT_FILENO, xy, sizeof(xy) - 1);
      printf ("%s", xy);

      return 0;
    }

  return -1;
}
