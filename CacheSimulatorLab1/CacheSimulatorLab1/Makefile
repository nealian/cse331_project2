CXX = g++
CXXFLAGS = -Wall -g -std=c++11

all: CacheSimulatorLab1

CacheSimulatorLab1: main.cpp AddressSplit.cpp AddressSplit.h NoWriteAllocate.cpp NoWriteAllocate.h SearchCache.cpp SearchCache.h CacheUpdate.cpp CacheUpdate.h
	$(CXX) $(CXXFLAGS) -o CacheSimulatorLab1 main.cpp AddressSplit.cpp NoWriteAllocate.cpp SearchCache.cpp CacheUpdate.cpp
