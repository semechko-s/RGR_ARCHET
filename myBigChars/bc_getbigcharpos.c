#include <myBigChars.h>

int
bc_getbigcharpos (int *big, int x, int y, int *value)
{
  if (!big || !value || x < 0 || x > 7 || y < 0 || y > 7)
    {
      return 1;
    }

  x--;
  y--;

  if (y < 4)
    {
      *value = (big[0] >> (y * 8 + x)) & 1;
    }
  else
    {
      *value = (big[1] >> (y * 8 + x)) & 1;
    }

  return 0;
}