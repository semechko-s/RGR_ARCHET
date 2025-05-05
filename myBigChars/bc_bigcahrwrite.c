#include <myBigChars.h>

int
bc_bigcharwrite (int fd, int *big, int count)
{
  if (!big || count < 0 || fd < 0)
    {
      return 1;
    }

  for (; count > 0; count--)
    {
      if (write (fd, &big[0], sizeof (int)) < 0)
        {
          return 1;
        }

      if (write (fd, &big[1], sizeof (int)) < 0)
        {
          return 1;
        }
    }

  return 0;
}