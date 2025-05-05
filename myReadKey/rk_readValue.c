#include <math.h>
#include <myReadKey.h>

int
rk_readValue (int *value, int timeout)
{
  if (!value)
    {
      return -1;
    }
  if (rk_mytermregime (1, timeout, 1, 1, 1) != 0)
    {
      return -1;
    }

  int sign = 0, command = 0, operand = 0;
  char temp_16[2];
  int temp_10[2];
  char buf;
  int i = 0, k = 0;

  // mt_gotoXY(20, 74);
  while (1)
    {
      scanf ("%c", &buf);
      if (buf == '+' || buf == '-')
        {
          printf ("%c", buf);
          break;
        }
    }

  sign = (buf == '-') ? 1 : 0;

  while (1)
    {
      scanf ("%c", &buf);
      if ((buf >= '0' && buf <= '9')
          || (buf == 'a' || buf == 'b' || buf == 'c' || buf == 'd'
              || buf == 'e' || buf == 'f'))
        {
          printf ("%c", buf);
          temp_16[i] = buf;
          i++;
          k++;
        }
      if (k == 2)
        {
          break;
        }
    }

  int j = 1;
  for (int i = 0; i < 2; i++)
    {
      switch (temp_16[i])
        {
        case '0':
          temp_10[i] = 0;
          break;
        case '1':
          temp_10[i] = 1;
          break;
        case '2':
          temp_10[i] = 2;
          break;
        case '3':
          temp_10[i] = 3;
          break;
        case '4':
          temp_10[i] = 4;
          break;
        case '5':
          temp_10[i] = 5;
          break;
        case '6':
          temp_10[i] = 6;
          break;
        case '7':
          temp_10[i] = 7;
          break;
        case '8':
          temp_10[i] = 8;
          break;
        case '9':
          temp_10[i] = 9;
          break;
        case 'a':
          temp_10[i] = 10;
          break;
        case 'b':
          temp_10[i] = 11;
          break;
        case 'c':
          temp_10[i] = 12;
          break;
        case 'd':
          temp_10[i] = 13;
          break;
        case 'e':
          temp_10[i] = 14;
          break;
        case 'f':
          temp_10[i] = 15;
          break;
        default:
          break;
        }

      command += temp_10[i] * pow (16, j);
      j--;
    }

  memset (temp_16, '\0', sizeof (temp_16));

  i = 0, k = 0;

  while (1)
    {
      scanf ("%c", &buf);
      if ((buf >= '0' && buf <= '9')
          || (buf == 'a' || buf == 'b' || buf == 'c' || buf == 'd'
              || buf == 'e' || buf == 'f'))
        {
          printf ("%c", buf);
          temp_16[i] = buf;
          i++;
          k++;
        }
      if (k == 2)
        {
          break;
        }
    }

  j = 1;
  for (int i = 0; i < 2; i++)
    {
      switch (temp_16[i])
        {
        case '0':
          temp_10[i] = 0;
          break;
        case '1':
          temp_10[i] = 1;
          break;
        case '2':
          temp_10[i] = 2;
          break;
        case '3':
          temp_10[i] = 3;
          break;
        case '4':
          temp_10[i] = 4;
          break;
        case '5':
          temp_10[i] = 5;
          break;
        case '6':
          temp_10[i] = 6;
          break;
        case '7':
          temp_10[i] = 7;
          break;
        case '8':
          temp_10[i] = 8;
          break;
        case '9':
          temp_10[i] = 9;
          break;
        case 'a':
          temp_10[i] = 10;
          break;
        case 'b':
          temp_10[i] = 11;
          break;
        case 'c':
          temp_10[i] = 12;
          break;
        case 'd':
          temp_10[i] = 13;
          break;
        case 'e':
          temp_10[i] = 14;
          break;
        case 'f':
          temp_10[i] = 15;
          break;
        default:
          break;
        }

      operand += temp_10[i] * pow (16, j);
      j--;
    }

  rk_mytermregime (1, timeout, 1, 0, 1);
  int x = 0;

  sc_commandEncode (sign, command, operand, &x);

  *value = x;

  return 0;
}