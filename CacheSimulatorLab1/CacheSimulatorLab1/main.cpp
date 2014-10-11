/*************************************************************************
/
/ filename: main.cpp
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

#include <iostream>
#include <iomanip>
#include "AddressSplit.h"
#include "NoWriteAllocate.h"
#include "SearchCache.h"
#include "CacheUpdate.h"

using namespace std;

void writeToCache(struct configData, struct addressSegments, struct traceLine, string [], int, int *, int *);
void readFromCache(struct configData, struct addressSegments, struct traceLine, string [], int, int *, int *);
string intToBinaryString(unsigned int);

int main(int argc, const char * argv[]) {
    string configFilename = argv[1]; // Config file is the first argument to the program
    string traceFilename = argv[2]; // Trace file is the second (and last) argument to the program
    ifstream traceFile (traceFilename);
    ofstream outFile (traceFilename + ".out");
    struct configData configDataFilled = readConfig(configFilename);
    const struct addressSegments addressSegmentsFilled = {log(configDataFilled.blockSize) / log(2),
							  configDataFilled.associativity ? log(configDataFilled.cacheSize*1024 / (configDataFilled.associativity * configDataFilled.blockSize)) / log(2) : 0,
							  ADDRESS_SIZE - (log(configDataFilled.blockSize) / log(2)) - (configDataFilled.associativity ? (log(configDataFilled.cacheSize*1024 / (configDataFilled.associativity * configDataFilled.blockSize)) / log(2)) : 0)};
    int cacheSize = configDataFilled.cacheSize * 1024 / ADDRESS_SIZE;
    int *cachedElements = calloc(cacheSize / (configDataFilled.associativity ? configDataFilled.associativity : 1),  sizeof(int));
    int *fifoCacheLocation = calloc(cacheSize / (configDataFilled.associativity ? configDataFilled.associativity : 1), sizeof(int));
    string cache[cacheSize];
    int loads = 0, loadHits = 0, stores = 0, storeHits = 0, currentIsHit;

    string currentTraceLineBuffer;
    

    while (getline(traceFile, currentTraceLineBuffer)) {
      struct traceLine currentTraceLine = readTraceLine(currentTraceLineBuffer);
      currentIsHit = cacheSearch(configDataFilled.associativity, intToBinaryString(currentTraceLine.address), cache, cachedElements);
      if (currentTraceLine.storeOrLoad == 's') {
        stores++;
	storeHits += currentIsHit;
	if (!currentIsHit)
	  writeToCache(configDataFilled, addressSegmentsFilled, currentTraceLine, cache, cacheSize, cachedElements, fifoCacheLocation);
      } else if (currentTraceLine.storeOrLoad == 'l') {
	loads++;
	loadHits += currentIsHit;
	if (!currentIsHit)
	  readFromCache(configDataFilled, addressSegmentsFilled, currentTraceLine, cache, cacheSize, cachedElements, fifoCacheLocation);
      } else {
	cout << "wtf?" << endl;
      }
    }

    outFile << (float) ((float) (storeHits + loadHits) / (float) (stores + loads)) << endl; // First output line: Total hit rate
    outFile << (float) ((float) loadHits / (float) loads) << endl; // Second output line: Load hit rate
    outFile << (float) ((float) storeHits / (float) stores) << endl; // Third output line: Store hit rate

    // cout << (int) cacheSearch(configDataFilled.associativity, "00011111111111111111011001000000", cache, cachedElements) << endl;
    
    cerr << cacheSize << endl;

    for(int j=0; j<cachedElements; j++) {
      cout << cache[j] << endl;
    }

    return 0;
}


void writeToCache(struct configData configDataFilled, struct addressSegments addressSegmentSizes, struct traceLine traceLineInfo, string cache[], int cacheSize, int *cachedElements, int *fifoCacheLocation)
{
    // if (configDataFilled.writeMissPolicy == NO_WRITE_ALLOCATE) {
    //   noWriteAllocate_write(configDataFilled, addressSegmentSizes, traceLineInfo.address, cache);
    // } else {
    //   //      writeAllocate_write(configDataFilled, addressSegmentSizes, traceLineInfo.address, cache);
    // }
}

void readFromCache(struct configData configDataFilled, struct addressSegments addressSegmentSizes, struct traceLine traceLineInfo, string cache[], int cacheSize, int *cachedElements, int *fifoCacheLocation)
{
  addElemToCache(configDataFilled, intToBinaryString(traceLineInfo.address), cache, cacheSize, cachedElements, fifoCacheLocation);
}

string intToBinaryString(unsigned int in)
{
  string bin = "01";
  int len = ADDRESS_SIZE;
  string result;
  do {
    result = bin[in % 2] + result;
    in /= 2;
    len--;
  } while(in || len);
  return result;
}
