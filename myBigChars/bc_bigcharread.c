#include <myBigChars.h>

int
bc_bigcharread (int fd, int *big, int need_count, int *count)
{
  if (!big || !count || fd < 0)
    {
      return 1;
    }

  for (; need_count > 0; need_count--)
    {
      if (read (fd, &big[0], sizeof (int)) < 0)
        {
          *count = 0;
          return 1;
        }

      if (read (fd, &big[1], sizeof (int)) < 0)
        {
          *count = 0;
          return 1;
        }
    }

  return 0;
}