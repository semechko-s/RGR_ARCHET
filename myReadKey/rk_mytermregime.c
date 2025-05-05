#include "rk_varibles.h"
#include <myReadKey.h>

int
rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint)
{

  if (regime == 1)
    { // некононичный
      tty.c_lflag &= ~ICANON;

      if (echo == 1)
        {
          tty.c_lflag &= ~ECHO;
        }
      else if (echo == 0)
        {
          tty.c_lflag |= ECHO;
        }
      else
        {
          write (STDERR_FILENO, "Uncorrect argument ECHO in rk_mytermregime\n",
                 43);
          return -1;
        }

      if (sigint == 1)
        {
          tty.c_lflag &= ~ISIG;
        }
      else if (sigint == 0)
        {
          tty.c_lflag |= ISIG;
        }
      else
        {
          write (STDERR_FILENO,
                 "Uncorrect argument SIGINT in rk_mytermregime\n", 43);
          return -1;
        }

      tty.c_cc[VMIN] = vmin;
      tty.c_cc[VTIME] = vtime;
    }
  else if (regime == 0)
    { // кононичный
      tty.c_lflag |= ICANON;
    }
  else
    {
      write (STDERR_FILENO, "Uncorrect argument REGIME in rk_mytermregime\n",
             43);
      return -1;
    }

  tcsetattr (0, TCSANOW, &tty);

  return 0;
}