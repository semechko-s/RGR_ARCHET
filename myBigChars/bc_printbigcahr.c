#include <myBigChars.h>

int
bc_printbigchar (int *a, int x, int y, enum Colors fg, enum Colors bg)
{
  if (!a || x < 1 || y < 1 || fg > 7 || fg < 0 || bg > 7 || bg < 0)
    {
      return 1;
    }
  mt_setfgcolor (fg);
  mt_setbgcolor (bg);

  printf ("\033(0");

  for (int k = 0; k < 2; k++)
    {
      for (int i = 0; i < 4; i++)
        {
          mt_gotoXY (y + i + k * 4, x);
          for (int j = 0; j < 8; j++)
            {
              if ((a[k] >> (i * 8 + j)) & 1)
                {
                  printf ("a");
                }
              else
                {
                  printf ("%c", ' ');
                }
            }
        }
    }

  printf ("\033(B");

  mt_setdefaultcolor ();
  printf ("\n");

  return 0;
}
