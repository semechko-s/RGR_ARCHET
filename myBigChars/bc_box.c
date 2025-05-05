#include <myBigChars.h>

int
bc_box (int x1, int y1, int x2, int y2, enum Colors box_fg, enum Colors box_bg,
        char *header, enum Colors header_fg, enum Colors header_bg)
{
  if (x1 < 1 || y1 < 1)
    {
      return -1;
    }

  mt_setfgcolor (box_fg);
  mt_setbgcolor (box_bg);
  printf ("\n");

  mt_gotoXY (x1, y1);

  printf ("\033(0");

  for (int i = 0; i < x2; i++)
    {
      if (i == 0)
        {
          printf ("%c", bc_cornerUpLeft);

          for (int j = 1; j < y2 - 1; j++)
            {
              printf ("%c", bc_horizontaleLine);
            }
          printf ("%c", bc_cornerUpRight);
          printf ("\n");
          continue;
        }
      mt_gotoXY (x1 + i, y1);
      printf ("%c", bc_verticalLine);

      for (int j = 1; j < y2 - 1; j++)
        {
          printf ("%c", ' ');
        }

      printf ("%c", bc_verticalLine);
      printf ("\n");

      if (i == x2 - 1)
        {
          mt_gotoXY (x1 + i, y1);
          printf ("%c", bc_cornerDownLeft);

          for (int j = 1; j < y2 - 1; j++)
            {
              printf ("%c", bc_horizontaleLine);
            }
          printf ("%c", bc_cornerDownRight);
          printf ("\n");
        }
    }

  if (header != NULL && bc_strlen (header) != 0)
    {
      mt_setfgcolor (header_fg);
      mt_setbgcolor (header_bg);
      mt_gotoXY (x1, y1 + y2 / 2 - bc_strlen (header) / 2);
      printf ("%s", header);
      printf ("\n");
    }

  printf ("\033(B");

  mt_setdefaultcolor ();
  printf ("\n");

  return 0;
}