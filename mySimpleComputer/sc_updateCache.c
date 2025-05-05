#include "../include/mySimpleComputer.h"

void
sc_updateCacheAfterSave (int memAddr, int cacheLine, int *value)
{
  static int currIndex = 0;
  static int countIt = 0;
  if (updateStatic == true)
    {
      currIndex = 0;
      countIt = 0;
      updateStatic = false;
    }
  *value = memory[memAddr];

  int addr = (cacheLine / 10) * 10;
  bool cacheCheck = false;
  for (int i = 0; i < CACHE_SIZE; ++i)
    {
      if (cache[i].addr == addr)
        {
          cacheCheck = true;
          currIndex = i;
          break;
        }
    }

  if (!cacheCheck)
    {
      if (countIt < CACHE_SIZE)
        {

          currIndex = countIt;
          for (int j = 0; j < CACHE_LINE_SIZE; ++j)
            {
              cache[currIndex].data[j] = memory[addr + j];
            }
          cache[currIndex].addr = addr;
          cache[currIndex].lastAT = time (NULL);
          countIt++;
        }
      else
        {
          currIndex = sc_RecentlyUsedCache ();
          for (int j = 0; j < CACHE_LINE_SIZE; ++j)
            {
              memory[cache[currIndex].addr + j] = cache[currIndex].data[j];
            }
          for (int j = 0; j < CACHE_LINE_SIZE; ++j)
            {
              cache[currIndex].data[j] = memory[addr + j];
            }
          cache[currIndex].addr = addr;
          cache[currIndex].lastAT = time (NULL);
        }
    }
  else
    {
      for (int j = 0; j < CACHE_LINE_SIZE; ++j)
        {
          cache[currIndex].data[j] = memory[addr + j];
        }
      cache[currIndex].lastAT = time (NULL);
    }
}