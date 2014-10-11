/*************************************************************************
/
/ filename: 
/
/ description: 
/
/ authors: Neal, Ian
/ Gallegos, Cristobal
/
/ class: CSE 331
/ instructor: Zheng
/ assignment: Lab Project #2
/
/ assigned: Oct 2, 2014
/ due: Oct 16, 2014
/
/************************************************************************/

#include "SearchCache.h"

int cacheSearch(unsigned int associativity, string searchItem, string cache[], int numCacheItems)
{
  if (associativity) {
    return nWaySearch(searchItem, cache, numCacheItems);
  } else {
    return fullyAssociativeSearch(searchItem, cache, numCacheItems);
  }
}

int fullyAssociativeSearch(string searchItem, string cache[], int numCacheItems)
{
  for (int i = 0; i < numCacheItems; i++) {
    if (cache[i] == searchItem)
      return 1;
  }
  return 0;
}

int nWaySearch(string searchItem, string cache[], int numCacheItems)
{
  return 0;
}
