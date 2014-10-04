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
    string filename = "../../CSE331-F14-Project2/sample.conf";
    struct configData configDataFilled = readConfig(filename);
    test(configDataFilled);
    return 0;
}
