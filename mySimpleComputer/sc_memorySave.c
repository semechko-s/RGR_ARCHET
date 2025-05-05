#include "../include/mySimpleComputer.h"

int
sc_memorySave (char *filename)
{
  FILE *file = fopen (filename, "wb");
  if (file == NULL)
    {
      return -1;
    }
  fwrite (memory, sizeof (int), SIZE, file);
  fclose (file);
  return 0;
}