//
//  AddressSplit.h
//  CacheSimulatorLab1
//
//  Created by Cristobal Gallegos on 10/4/14.
//  Copyright (c) 2014 Cristobal Gallegos. All rights reserved.
//

#ifndef __CacheSimulatorLab1__AddressSplit__
#define __CacheSimulatorLab1__AddressSplit__

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct configData
{
    unsigned int blockSize;
    unsigned int cacheSize;
    unsigned int missPenalty;
    char associativity;
    char writeMissPolicy;
    char replacementPolicy;
};

struct configData readConfig(string);
void test(struct configData);

#endif /* defined(__CacheSimulatorLab1__AddressSplit__) */

