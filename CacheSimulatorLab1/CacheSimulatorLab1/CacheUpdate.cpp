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

#include "CacheUpdate.h"

void addElemToCache(struct configData configDataFilled, struct addressSegments addressSegmentSizes, string elem, string cache[], unsigned int cacheSize, unsigned int *cachedElements, unsigned int *fifoCacheLocation)
{
  if (configDataFilled.associativity) {
    addElemToCacheNWay(configDataFilled, addressSegmentSizes, elem, cache, cacheSize, cachedElements, fifoCacheLocation);
  } else {
    if (*cachedElements < cacheSize) {
      cache[(*cachedElements)++] = elem;
      (*fifoCacheLocation)++;
    } else {
      if (configDataFilled.replacementPolicy == RANDOM_REPLACEMENT) {
	evictAndReplaceRandom(elem, cache, cacheSize);
      } else if(configDataFilled.replacementPolicy == FIFO_REPLACEMENT) {
	*fifoCacheLocation = (*fifoCacheLocation + 1) % cacheSize;
	evictAndReplaceFifo(elem, cache, *fifoCacheLocation);
      }
    }
  }

}

void addElemToCacheNWay(struct configData configDataFilled, struct addressSegments addressSegmentSizes, string elem, string cache[], unsigned int cacheSize, unsigned int cachedElements[], unsigned int fifoCacheLocation[])
{
  unsigned int curSet = stoi(getSetIndex(addressSegmentSizes, elem), 0, 2);
  if (cachedElements[curSet] < configDataFilled.associativity) {
    cache[curSet * configDataFilled.associativity + cachedElements[curSet]++] = elem;
    fifoCacheLocation[curSet]++;
  } else {
    if (configDataFilled.replacementPolicy == RANDOM_REPLACEMENT) {
      evictAndReplaceRandomNWay(elem, cache, configDataFilled.associativity, curSet);
    } else if (configDataFilled.replacementPolicy == FIFO_REPLACEMENT) {
      fifoCacheLocation[curSet] = (fifoCacheLocation[curSet] + 1) % configDataFilled.associativity;
      evictAndReplaceFifoNWay(elem, cache, configDataFilled.associativity, curSet, fifoCacheLocation[curSet]);
    } else {
      cout << "wtf?" << endl;
    }
  }
}

void evictAndReplaceRandom(string elem, string cache[], unsigned int cacheSize)
{
  int cacheReplace = rand() % cacheSize;
  cache[cacheReplace] = elem;
}

void evictAndReplaceFifo(string elem, string cache[], unsigned int fifoCacheLocation)
{
  cache[fifoCacheLocation] = elem;
}

void evictAndReplaceRandomNWay(string elem, string cache[], unsigned int associativity, unsigned int curSet)
{
  int cacheReplace = rand() % associativity;
  cache[associativity * curSet + cacheReplace] = elem;
}

void evictAndReplaceFifoNWay(string elem, string cache[], unsigned int associativity, unsigned int curSet, unsigned int fifoCacheLocation)
{
  cache[associativity * curSet + fifoCacheLocation] = elem;
}
