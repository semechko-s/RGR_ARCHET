#include "../include/mySimpleComputer.h"

int
sc_RecentlyUsedCache ()
{
  int leastRecentlyUsedIndex = 0;
  time_t leastRecentTime = cache[0].lastAT;
  for (int i = 1; i < CACHE_SIZE; ++i)
    {
      if (cache[i].lastAT < leastRecentTime)
        {
          leastRecentTime = cache[i].lastAT;
          leastRecentlyUsedIndex = i;
        }
    }
  return leastRecentlyUsedIndex;
}