//
//  main.cpp
//  CacheSimulatorLab1
//
//  Created by Cristobal Gallegos on 10/4/14.
//  Copyright (c) 2014 Cristobal Gallegos. All rights reserved.
//

#include <iostream>
#include "AddressSplit.h"
using namespace std;

int main(int argc, const char * argv[]) {
    string filename = argv[1]; // Filename is the first argument to the program
    struct configData configDataFilled = readConfig(filename);
    uint32_t *cache = (uint32_t *) malloc(configDataFilled.cacheSize);
    const int blockIndexSize = log(configDataFilled.blockSize) / log(2);
    const int setIndexSize = log(configDataFilled.cacheSize*1024 / (2 * configDataFilled.blockSize)) / log(2);
    const int tagSize = ADDRESS_SIZE - blockIndexSize - setIndexSize;

    cout << blockIndexSize << endl;
    cout << setIndexSize << endl;
    cout << tagSize << endl;

    return 0;
}
