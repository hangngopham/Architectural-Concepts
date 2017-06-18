#include "CacheSet.h"
#include<iostream>
#include<fstream>
#include<cstring>
#include<sstream>
#include<cstdlib>

using namespace std;

CacheSet::CacheSet(int cache_size,int block_size,int associativity) {
	if(cache_size <= 0) {
		cout<< "Cache size must be positive" << endl;
		exit(-1);
	}	
	
	if(block_size <= 0) {
		cout << "Block size must be positive" << endl;
		exit(-1);
	}
	
	if(associativity <= 0) {
		cout << "Set associativity must be greater than 0" << endl;
		exit(-1);
	}

	this->cache_size = cache_size;
	this->block_size = block_size;
	this->associativity = associativity;
	numSets = (cache_size/(block_size*associativity));
	wb = 0;
	this->cacheSet.assign((unsigned int)numSets,Set(associativity));

	readHits = 0;
	readMisses = 0;
	writeHits = 0;
	writeMisses = 0;
}


// Calculate tag 
unsigned int CacheSet::numTag(unsigned int address) {
	return (address/(block_size*4))/numSets;
}

// Calculate index
unsigned int CacheSet::countIndex(unsigned int address) {
	return (address/(block_size*4))%(numSets);
}

// Count number of misses and hits.
// Miss = 0
// Hits = 1
// Dirty and misses = 2

void CacheSet::count_Misses_Hits(unsigned long address, bool write) {
	int temp = cacheSet[countIndex(address)].check(numTag(address),write);

	if(write) {
		if(temp == 1) {
			writeHits++;
		}
		else if(temp == 2) {
			writeMisses;
			wb++;
		}
		else {
			writeMisses++;
		}
	}
	else {
		if(temp == 1) {
			readHits++;
		}
		else if(temp == 2) {
			readMisses;
			wb++;
		}
		else {
			readMisses++;
		}
	}
}

// Display the total number of reads, the total number of writes, 
// the number of reads that resulted in cache misses, the number 
// of writes that resulted in cache misses, the overall hit rate 
// and the average memory access time. 
void CacheSet::print(bool writeback) {
	int writeMem = 0;
	int total = readHits + readMisses + writeHits + writeMisses;
	cout << "Cache size: " << cache_size << endl;
	cout << "Block size: " << block_size << endl;


	cout << "Number of readHits: " << readHits << endl;
	cout << "Number of readMisses: " << readMisses << endl;
	cout << "Total number of reads: " << (readHits + readMisses) << endl;

	cout << "Number of writeHits: " << writeHits << endl;
	cout << "Number of writeMisses: " << writeMisses << endl;
	cout << "Total number of writes: " << (writeHits + writeMisses) << endl;
	 
	cout << "Total hits: " << readHits + writeHits << endl;
	cout << "Total misses: " << readMisses + writeMisses << endl;
	cout << "Total hits and reads: " << total << endl;
	cout << "Number of memory accesses: " << total <<endl;

	if(writeback) {
		cout << "Write to memory (write back): " << wb << endl;
	}
	else {
		cout << "Write to memory (write through): " << writeHits + writeMisses << endl;
	}

	int overhead = cache_size/block_size;
	
	cout << "Overhead bytes: " << overhead << endl;
	cout << "The overall hit rate: " << (double)(readHits + writeHits)/(double)total << endl;
}	
// destructor
CacheSet::~CacheSet() {
}
