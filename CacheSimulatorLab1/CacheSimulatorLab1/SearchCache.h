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

#ifndef __search_cache_h__
#define __search_cache_h__

#include <string>

using namespace std;

int cacheSearch(unsigned int associativity, string SearchItem, string cache[], int numCacheItems);
int fullyAssociativeSearch(string searchItem, string cache[], int numCacheItems);
int nWaySearch(string searchItem, string cache[], int numCacheItems);

#endif
