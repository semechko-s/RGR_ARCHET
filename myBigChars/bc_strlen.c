#include <myBigChars.h>

int
bc_strlen (char *str)
{
  if (str == NULL)
    {
      return -1;
    }

  size_t length = 0;
  while (*str)
    {
      unsigned char c = *str;
      size_t char_length = 0;

      if ((c & 0x80) == 0)
        {
          char_length = 1;
        }
      else if ((c & 0xE0) == 0xC0)
        {
          char_length = 2;
        }
      else if ((c & 0xF0) == 0xE0)
        {
          char_length = 3;
        }
      else if ((c & 0xF8) == 0xF0)
        {
          char_length = 4;
        }
      else
        {
          return -1;
        }

      for (size_t i = 1; i < char_length; ++i)
        {
          if ((str[i] & 0xC0) != 0x80)
            {
              return -1;
            }
        }

      str += char_length;
      ++length;
    }

  return length;
}