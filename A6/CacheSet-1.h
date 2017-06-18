#ifndef CACHE_SET_H
#define CACHE_SET_H
#include "Set.h"
#include<iostream>
#include<string>
#include<vector>

using namespace std;

class CacheSet {
	private:		
		vector<Set> cacheSet;
		int cache_size;
		int block_size;
		int index_size;
		int numSets;
		int associativity;
		int readHits;
		int readMisses;
		int writeHits;
		int writeMisses;
		int wb;
		
	public:
		CacheSet(int,int,int);	
		unsigned int numTag(unsigned int);
		unsigned int countIndex(unsigned int);
		void count_Misses_Hits(unsigned long, bool);
		void print(bool);
		~CacheSet();		
};
#endif
