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

#ifndef __search_cache_h__
#define __search_cache_h__

#include "AddressSplit.h"
#include <string>

using namespace std;

int cacheSearch(unsigned int associativity, struct addressSegments addressSegmentSizes, string searchItem, string cache[], unsigned int *numCacheItems);
int fullyAssociativeSearch(string searchItem, string cache[], unsigned int numCacheItems);
int nWaySearch(unsigned int associativity, struct addressSegments addressSegmentSizes, string searchItem, string cache[], unsigned int numCacheItems[]);

#endif
