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

#ifndef __cache_update_h__
#define __cache_update_h__

#include "AddressSplit.h"
#include <cstdlib>

using namespace std;

void addElemToCache(struct configData configDataFilled, struct addressSegments addressSegmentSizes, string elem, string cache[], unsigned int cacheSize, unsigned int *cachedElements, unsigned int *fifoCacheLocation);
void addElemToCacheNWay(struct configData configDataFilled, struct addressSegments addressSegmentSizes, string elem, string cache[], unsigned int cacheSize, unsigned int cachedElements[], unsigned int fifoCacheLocation[]);
void evictAndReplaceRandom(string elem, string cache[], unsigned int cacheSize);
void evictAndReplaceFifo(string elem, string cache[], unsigned int fifoCacheLocation);
void evictAndReplaceRandomNWay(string elem, string cache[], unsigned int associativity, unsigned int curSet);
void evictAndReplaceFifoNWay(string elem, string cache[], unsigned int associativity, unsigned int curSet, unsigned int fifoCacheLocation);
#endif
