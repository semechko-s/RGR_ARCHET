#include "../include/simplebasic.h"

int
main (int argc, char **argv)
{
  FILE *file_sb, *file_sa;

  if ((file_sb = fopen (argv[1], "rb")) <= 0)
    {
      printf ("Can`t open '%s' file.\n", argv[1]);
      return -1;
    }
  if ((file_sa = fopen (argv[2], "wb")) <= 0)
    {
      printf ("Can`t create '%s' file.\n", argv[2]);
      return -1;
    }
  basicToAss (file_sb, file_sa);
  return 0;
}