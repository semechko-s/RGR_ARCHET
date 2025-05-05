#include <myBigChars.h>

int
bc_setbigcharpos (int *big, int x, int y, int value)
{
  if (!big || x < 0 || x > 7 || y < 0 || y > 7 || value < 0 || value > 1)
    {
      return 1;
    }

  y--;
  x--;

  if (y < 4)
    {
      if (value)
        {
          big[0] |= 1 << (y * 8 + x);
        }
      else
        {
          big[0] = ~(1 << (y * 8 + x));
        }
    }
  else
    {
      if (value)
        {
          big[1] |= 1 << (y * 8 + x);
        }
      else
        {
          big[1] = ~(1 << (y * 8 + x));
        }
    }

  return 0;
}
