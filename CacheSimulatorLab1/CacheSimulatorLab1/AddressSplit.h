/*************************************************************************
/
/ filename: AddressSplit.h
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

#ifndef __CacheSimulatorLab1__AddressSplit__
#define __CacheSimulatorLab1__AddressSplit__

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>


#define ADDRESS_SIZE 32
#define NO_WRITE_ALLOCATE 0
#define WRITE_ALLOCATE 1
#define RANDOM_REPLACEMENT 0
#define FIFO_REPLACEMENT 1

using namespace std;

struct configData
{
    unsigned int blockSize;
    unsigned int cacheSize;
    unsigned int missPenalty;
    unsigned int associativity;
    char writeMissPolicy;
    char replacementPolicy;
};

struct addressSegments
{
  int blockIndexSize;
  int setIndexSize;
  int tagSize;
};

struct traceLine
{
  char storeOrLoad;
  unsigned int address;
  unsigned int numInstructionsBefore;
};

struct configData readConfig(string);
struct traceLine readTraceLine(string);
string getSetIndex(struct addressSegments addressSegmentSizes, string address);
string getTag(struct addressSegments addressSegmentSizes, string address);

#endif /* defined(__CacheSimulatorLab1__AddressSplit__) */

