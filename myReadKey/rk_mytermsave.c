#include "rk_varibles.h"
#include <myReadKey.h>

int
rk_mytermsave ()
{
  tcgetattr (STDIN_FILENO, &tty);
  savetty = tty;

  return 0;
}