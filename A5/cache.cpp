#include "cache.h"
#include<iostream>
#include<fstream>
#include<cstring>
#include<sstream>
#include<cstdlib>

using namespace std;

Cache::Cache(int cache_size,int block_size,int miss_time) {
	if(cache_size <= 0) {
		cout<< "Cache size must be positive" << endl;
		exit(-1);
	}	
	
	if(block_size <= 0) {
		cout << "Block size must be positive" << endl;
		exit(-1);
	}

	this->cache_size = cache_size;
	this->block_size = block_size;
	this->miss_time = miss_time;
	numBlocks = (cache_size/block_size);

	read_hits = 0;
	read_misses = 0;
	write_hits = 0;
	write_misses = 0;

	cache = new int[numBlocks];

	int i = 0;
	for(i = 0; i < numBlocks; i++) {
		cache[i] = -1;
	}
}	

// Calculate tag 
unsigned int Cache::numTag(unsigned int address) {
	return (address/(block_size*4))/numBlocks;
}

// Calculate index
unsigned int Cache::countIndex(unsigned int address) {
	return (address/(block_size*4))%numBlocks;
}

// Count number of misses and hits
void Cache::count_Misses_Hits(unsigned int address, bool read) {
	int tag, index;
	if(numTag(address) != cache[countIndex(address)]) {
		if(read) {
			read_misses++;
		}
		else {
			write_misses++;
		}
		tag = numTag(address);
		index = countIndex(address);
		cache[index] = tag;
	}
	else {
		if(read) {
			read_hits++;
		}
		else {
			write_hits++;
		}
	}
}

// Display the total number of reads, the total number of writes, 
// the number of reads that resulted in cache misses, the number 
// of writes that resulted in cache misses, the overall hit rate 
// and the average memory access time. 
void Cache::print() {
	int total = read_hits + read_misses + write_hits + write_misses;
	cout << "Block size: " << block_size << endl;
	cout << "Cache size: " << cache_size << endl;
	cout << "Miss time: " << miss_time << endl;

	cout << "Number of read_hits: " << read_hits << endl;
	cout << "Number of read_misses: " << read_misses << endl;
	cout << "Total number of reads: " << (read_hits + read_misses) << endl;

	cout << "Number of write_hits: " << write_hits << endl;
	cout << "Number of write_misses: " << write_misses << endl;
	cout << "Total number of writes: " << (write_hits + write_misses) << endl;
	 
	cout << "Total hits: " << read_hits + write_hits << endl;
	cout << "Total misses: " << read_misses + write_misses << endl;
	cout << "Total hits and reads: " << total << endl;
	cout << "The overall hit rate: " << (double)(read_hits + write_hits)/(double)total << endl;
	cout << "Average memory access time (cycles): " << (double) (read_hits + write_hits + (read_misses + write_misses)*miss_time)/(double)total << endl;
}
// destructor
Cache::~Cache() {
}
