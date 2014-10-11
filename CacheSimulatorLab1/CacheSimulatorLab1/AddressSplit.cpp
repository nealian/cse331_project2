/*************************************************************************
/
/ filename: AddressSplit.cpp
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

#include "AddressSplit.h"

using namespace std;

/**
 * Method to grab data from config file
 * @param string filename
 * @return struct configData
 */

struct configData readConfig(string filename)
{
    ifstream file (filename);
    struct configData configDataFilled;
    string lineBuffer;
    
    getline(file, lineBuffer); // First line is block size (line size); non-negative power of 2
    configDataFilled.blockSize = stoi(lineBuffer);
    
    getline(file, lineBuffer); // Second line is associativity; 0 = fully associative, 1 = direct-mapped,
                               // otherwise, # of ways associative
    configDataFilled.associativity = stoi(lineBuffer);
    
    getline(file, lineBuffer); // Third line is cache size (data size); non-negative power of 2, in KB
    configDataFilled.cacheSize = stoi(lineBuffer);
    
    getline(file, lineBuffer); // Fourth line is replacement policy; 0 for random, 1 for FIFO
    configDataFilled.replacementPolicy = (char) stoi(lineBuffer);
    
    getline(file, lineBuffer); // Fifth line is miss penalty; may be any positive integer
    configDataFilled.missPenalty = stoi(lineBuffer);
    
    getline(file, lineBuffer); // Sixth line is write miss policy (write allocate); 0 is no-write-allocate,
                               // write-through, 1 is write-allocate, write-back
    configDataFilled.writeMissPolicy = (char) stoi(lineBuffer);
    
    return configDataFilled;
}

struct traceLine readTraceLine(string line)
{
  struct traceLine traceLineInfo;

  if (3 == sscanf(line.c_str(), "%c %x %u", &(traceLineInfo.storeOrLoad), &(traceLineInfo.address), &(traceLineInfo.numInstructionsBefore)))
    return traceLineInfo;

  cout << "whoops!" << endl;
  exit(1);
}




