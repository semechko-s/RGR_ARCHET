#include <stdio.h>

unsigned long long
generateDecimalFromMatrixTop (int matrix[4][8])
{
  unsigned long long decimal = 0;
  for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < 8; j++)
        {
          decimal |= (matrix[i][j] & 1) << (i * 8 + j);
        }
    }
  return decimal;
}

unsigned long long
generateDecimalFromMatrixBottom (int matrix[4][8])
{
  unsigned long long decimal = 0;
  for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < 8; j++)
        {
          decimal |= (matrix[i][j] & 1) << (i * 8 + j);
        }
    }
  return decimal;
}

int
main ()
{
  int matrixPlusTop[4][8] = { { 0, 0, 0, 0, 0, 0, 0, 0 },
                              { 0, 1, 1, 1, 1, 1, 1, 0 },
                              { 0, 1, 1, 0, 0, 0, 0, 0 },
                              { 0, 1, 1, 0, 0, 0, 0, 0 } };

  int matrixPlusBottom[4][8] = { { 0, 1, 1, 1, 1, 1, 1, 0 },
                                 { 0, 1, 1, 0, 0, 0, 0, 0 },
                                 { 0, 1, 1, 0, 0, 0, 0, 0 },
                                 { 0, 0, 0, 0, 0, 0, 0, 0 } };

  unsigned long long decimalPlusTop
      = generateDecimalFromMatrixTop (matrixPlusTop);

  unsigned long long decimalPlusBottom
      = generateDecimalFromMatrixBottom (matrixPlusBottom);

  printf ("Decimal representation of top part of '+': %llu\n", decimalPlusTop);
  printf ("Decimal representation of bottom part of '+': %llu\n",
          decimalPlusBottom);

  return 0;
}
