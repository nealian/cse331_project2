/*************************************************************************
/
/ filename: CacheUpdate.h
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

#ifndef __cache_update_h__
#define __cache_update_h__

#include "AddressSplit.h"
#include <cstdlib>

using namespace std;

void addElemToCache(struct configData configDataFilled, string elem, string cache[], int cacheSize, int *cachedElements, int *fifoCacheLocation);
void addElemToCacheNWay(struct configData configDataFilled, struct addressSegments addressSegmentSizes, string elem, string cache[], int cacheSize, int cachedElements[], int fifoCacheLocation[]);
void evictAndReplaceRandom(string elem, string cache[], int cacheSize);
void evictAndReplaceFifo(string elem, string cache[], int fifoCacheLocation);
void evictAndReplaceRandomNWay(string elem, string cache[], int associativity, int curSet);
void evictAndReplaceFifoNWay(string elem, string cache[], int associativity, int curSet, int fifoCacheLocation);

#endif
