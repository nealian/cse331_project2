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
 ************************************************************************/

#include "SearchCache.h"

int cacheSearch(unsigned int associativity, struct addressSegments addressSegmentSizes, string searchItem, string cache[], unsigned int *numCacheItems)
{
  if (associativity) {
    return nWaySearch(associativity, addressSegmentSizes, searchItem, cache, numCacheItems);
  } else {
    return fullyAssociativeSearch(searchItem, cache, *numCacheItems);
  }
}

int fullyAssociativeSearch(string searchItem, string cache[], unsigned int numCacheItems)
{
  for (unsigned int i = 0; i < numCacheItems; i++) {
    if (cache[i] == searchItem)
      return 1;
  }
  return 0;
}

int nWaySearch(unsigned int associativity, struct addressSegments addressSegmentSizes, string searchItem, string cache[], unsigned int numCacheItems[])
{
  int curSet = stoi(getSetIndex(addressSegmentSizes, searchItem), 0, 2);
  if (numCacheItems[curSet]) {
    for (unsigned int i = 0; i < numCacheItems[curSet]; i++) {
      if (cache[associativity * curSet + i] == searchItem)
	return 1;
    }
  }
  return 0;
}
