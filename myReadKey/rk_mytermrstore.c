#include "rk_varibles.h"
#include <myReadKey.h>

int
rk_mytermrestore ()
{
  if (tcsetattr (STDIN_FILENO, TCSANOW, &savetty) != 0)
    {
      return 1;
    }

  return 0;
}