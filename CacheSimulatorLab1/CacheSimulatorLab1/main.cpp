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

#include <iostream>
#include <iomanip>
#include "AddressSplit.h"

#include "SearchCache.h"
#include "CacheUpdate.h"

using namespace std;

void writeToCacheOnMiss(struct configData configDataFilled, struct addressSegments addressSegmentSizes, struct traceLine traceLineInfo, string cache[], unsigned int cacheSize, unsigned int *cachedElements, unsigned int *fifoCacheLocation);
void readFromCacheOnMiss(struct configData configDataFilled, struct addressSegments addressSegmentSizes, struct traceLine traceLineInfo, string cache[], unsigned int cacheSize, unsigned int *cachedElements, unsigned int *fifoCacheLocation);
string intToBinaryString(unsigned int in);

int main(int argc, const char * argv[]) {
    string configFilename = argv[1]; // Config file is the first argument to the program
    string traceFilename = argv[2]; // Trace file is the second (and last) argument to the program
    ifstream traceFile (traceFilename);
    ofstream outFile (traceFilename + ".out");
    struct configData configDataFilled = readConfig(configFilename);
    unsigned int blockIndexSize = (unsigned int) log2(configDataFilled.blockSize);
    unsigned int numBlocks = configDataFilled.cacheSize*1024 / configDataFilled.blockSize;
    unsigned int numSets = numBlocks / configDataFilled.associativity;
    unsigned int setIndexSize = (unsigned int) log2(numSets);
    unsigned int tagSize = ADDRESS_SIZE - blockIndexSize - setIndexSize;
    const struct addressSegments addressSegmentsFilled = {blockIndexSize,
                                                          setIndexSize,
                                                          tagSize};
    unsigned int *cachedElements = (unsigned int *) calloc(numSets,  sizeof(unsigned int));
    unsigned int *fifoCacheLocation = (unsigned int *) calloc(numSets, sizeof(unsigned int));
    string cache[numBlocks];
    unsigned int loads = 0, loadHits = 0, stores = 0, storeHits = 0, currentIsHit, otherOperations = 0;

    string currentTraceLineBuffer;
    

    while (getline(traceFile, currentTraceLineBuffer)) {
      struct traceLine currentTraceLine = readTraceLine(currentTraceLineBuffer);
      currentIsHit = cacheSearch(configDataFilled.associativity, addressSegmentsFilled, intToBinaryString(currentTraceLine.address), cache, cachedElements);
      otherOperations += currentTraceLine.numInstructionsBefore;
      if (currentTraceLine.storeOrLoad == 's') {
        stores++;
	storeHits += currentIsHit;
	if (!currentIsHit)
	  writeToCacheOnMiss(configDataFilled, addressSegmentsFilled, currentTraceLine, cache, numBlocks, cachedElements, fifoCacheLocation);
      } else if (currentTraceLine.storeOrLoad == 'l') {
	loads++;
	loadHits += currentIsHit;
	if (!currentIsHit)
	  readFromCacheOnMiss(configDataFilled, addressSegmentsFilled, currentTraceLine, cache, numBlocks, cachedElements, fifoCacheLocation);
      } else {
	cout << "wtf?" << endl;
      }
    }

    outFile << (float) ((float) (storeHits + loadHits) / (float) (stores + loads)) << endl; // First output line: Total hit rate
    outFile << (float) ((float) loadHits / (float) loads) << endl; // Second output line: Load hit rate
    outFile << (float) ((float) storeHits / (float) stores) << endl; // Third output line: Store hit rate
    outFile << (otherOperations + (storeHits + loadHits) + ((stores + loads) - (storeHits + loadHits)) * configDataFilled.missPenalty) << endl; // Fourth output line: Total run time in cycles (we're assuming that the last trace line entry is in cycles)
    outFile << (float) (1 + (1 - (float) ((float) (storeHits + loadHits) / (float) (stores + loads))) * configDataFilled.missPenalty) << endl; // Fifth (last) output line: Average memory access latency, in cycles, with a hit as 1 cycle. (Using 1 - hit rate as miss rate)

    // cout << (int) cacheSearch(configDataFilled.associativity, addressSegmentsFilled, "00011111111111111111011001000000", cache, cachedElements) << endl;
    
    // cerr << numBlocks << endl;

    // for(unsigned int j=0; j<numBlocks; j++) {
    // 	cout << cache[j] << endl;
    // }

    return 0;
}


void writeToCacheOnMiss(struct configData configDataFilled, struct addressSegments addressSegmentSizes, struct traceLine traceLineInfo, string cache[], unsigned int cacheSize, unsigned int *cachedElements, unsigned int *fifoCacheLocation)
{
  if (configDataFilled.writeMissPolicy == WRITE_ALLOCATE) {
    addElemToCache(configDataFilled, addressSegmentSizes, intToBinaryString(traceLineInfo.address), cache, cacheSize, cachedElements, fifoCacheLocation);
  }
}

void readFromCacheOnMiss(struct configData configDataFilled, struct addressSegments addressSegmentSizes, struct traceLine traceLineInfo, string cache[], unsigned int cacheSize, unsigned int *cachedElements, unsigned int *fifoCacheLocation)
{
  addElemToCache(configDataFilled, addressSegmentSizes, intToBinaryString(traceLineInfo.address), cache, cacheSize, cachedElements, fifoCacheLocation);
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
