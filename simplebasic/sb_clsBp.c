#include "../include/simplebasic.h"

void
sb_clearBackspace (char *str)
{
  char *current = str;
  char *last = str;

  for (; *current != '\0'; ++current)
    {
      if (*current != ' ')
        {
          *last = *current;
          last++;
        }
    }
  *last = '\0';
}