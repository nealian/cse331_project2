//
//  AddressSplit.cpp
//  CacheSimulatorLab1
//
//  Created by Cristobal Gallegos on 10/4/14.
//  Copyright (c) 2014 Cristobal Gallegos. All rights reserved.
//

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
    
    getline(file, lineBuffer); // Second line is associativity; 0 or 1
    configDataFilled.associativity = (char) stoi(lineBuffer);
    
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

void test(struct configData configDataFilled)
{
    cout << configDataFilled.blockSize << endl;
    cout << (int) configDataFilled.associativity << endl;
    cout << configDataFilled.cacheSize << endl;
    cout << (int) configDataFilled.replacementPolicy << endl;
    cout << configDataFilled.missPenalty << endl;
    cout << (int) configDataFilled.writeMissPolicy << endl;
}





