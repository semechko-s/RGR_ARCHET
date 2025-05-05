#include "rk_varibles.h"
#include <myReadKey.h>

int
rk_readkey (enum keys *key)
{
  rk_mytermsave ();

  char buf[6] = { 0 };
  rk_mytermregime (1, 0, 1, 1, 1);

  read (STDIN_FILENO, buf, 6);

  if (strcmp (buf, "\E[C") == 0)
    {
      *key = RIGHT;
    }
  else if (strcmp (buf, "\E[D") == 0)
    {
      *key = LEFT;
    }
  else if (strcmp (buf, "\E[A") == 0)
    {
      *key = UP;
    }
  else if (strcmp (buf, "\E[B") == 0)
    {
      *key = DOWN;
    }
  else if (strcmp (buf, "\E[15~") == 0)
    {
      *key = F5;
    }
  else if (strcmp (buf, "\E[17~") == 0)
    {
      *key = F6;
    }
  else if (strcmp (buf, "\E") == 0)
    {
      *key = ESC;
    }
  else if (strcmp (buf, "-") == 0)
    {
      *key = MINUS;
    }
  else if (strcmp (buf, "+") == 0)
    {
      *key = PLUS;
    }
  else if (strcmp (buf, "\n") == 0)
    {
      *key = ENTER;
    }

  else if (buf[0] >= 48 && buf[0] < 58)
    {
      *key = buf[0] - 48;
    }
  else if (buf[0] > 64 && buf[0] < 91)
    {
      *key = buf[0];
    }
  else if (buf[0] > 96 && buf[0] < 123)
    {
      *key = buf[0];
    }
  else if (buf[0] == 17)
    {
      *key = buf[0] + 28;
    }
  else if (buf[0] == 18)
    {
      *key = buf[0] + 25;
    }
  else
    {
      *key = OTHER;
    }

  rk_mytermrestore ();

  return 0;
}