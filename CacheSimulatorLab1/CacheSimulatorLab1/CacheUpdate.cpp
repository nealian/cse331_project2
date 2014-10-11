/*************************************************************************
/
/ filename: CacheUpdate.cpp
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

#include "CacheUpdate.h"

void addElemToCache(struct configData configDataFilled, string elem, string cache[], int cacheSize, int *cachedElements, int *fifoCacheLocation)
{
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

void addElemToCacheNWay(struct configData configDataFilled, struct addressSegments addressSegmentSizes, string elem, string cache[], int cacheSize, int cachedElements[], int fifoCacheLocation[])
{
  int numSets = cacheSize / configDataFilled.associativity;
  int curSet = stoi(getSetIndex(addressSegmentSizes, elem), 2);
  if (cachedElements[curSet] < configDataFilled.associativity) {
    cache[curSet * configDataFilled.associativity + cachedElements[curSet]++];
    fifoCacheLocation[curSet]++;
  } else {
    if (configDataFilled.replacementPolicy == RANDOM_REPLACEMENT) {
      evictAndReplaceRandomNWay(elem, cache, configDataFilled.associativity, curSet);
    } else if (configDataFilled.replacementPolicy == FIFO_REPLACEMENT) {
      evictAndReplaceFifoNWay(elem, cache, configDataFilled.associativity, curSet, fifoCacheLocation[curSet]);
    } else {
      cout << "wtf?" << endl;
    }
  }
}

void evictAndReplaceRandom(string elem, string cache[], int cacheSize)
{
  int cacheReplace = rand() % cacheSize;
  cache[cacheReplace] = elem;
}

void evictAndReplaceFifo(string elem, string cache[], int fifoCacheLocation)
{
  cache[fifoCacheLocation] = elem;
}

void evictAndReplaceRandomNWay(string elem, string cache[], int associativity, int curSet)
{
  int cacheReplace = rand() % associativity;
  cache[associativity * curSet + cacheReplace] = elem;
}

void evictAndReplaceFifoNWay(string elem, string cache[], int associativity, int curSet, int fifoCacheLocation)
{
  cache[associativity * curSet + fifoCacheLocation] = elem;
}
