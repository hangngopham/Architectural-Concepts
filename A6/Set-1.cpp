#include "Set.h"
#define HIT 1
#define DIRTY_MISS 2
#define MISS 0
#include<iostream>
#include<fstream>
#include<cstring>
#include<sstream>
#include<cstdlib>

using namespace std;

// constructor
Set::Set(int s) {
	counter = 0;
	num = 0;
	size = s;
	for(int i = 0; i < size; i++) {
		cacheLines[i] = Set::cacheLine();			
	}

}

// Find the least recently used 
void Set::getLRU(int counter) {
	for(int i = 0; i < size; i++) {
		cacheLines[i].lru = cacheLines[i].lru + 1;
	}
	cacheLines[counter].lru = 0;
	int maxIndex = 0;
	for(int i = 0; i < size; i++) {
		if(cacheLines[i].lru > maxIndex) {
			maxIndex = cacheLines[i].lru;
			num = i;
		}		
	}
}

// Check if the line is dirty - miss and replace the line
bool Set:: replaceLine(cacheLine line) {
	bool dm = cacheLines[num].d;		
	cacheLines[num] = line;
	getLRU(num);
	return dm;
}

// Check if it is a hit (1), a miss (0) or a dirty - miss (2)
int Set::check(unsigned int tag, bool write) {
	for(int i = 0; i < counter; i++) {
		if(tag == cacheLines[i].tag) {
			if(cacheLines[i].v == true) {
				if(counter == size) {
					getLRU(i);
				}
				return 1;
	  		}
		}
	}

	cacheLine line;
	if(write) {
		line.d = true;
	}

	line.tag = tag;
	line.v = true;
	
	if(counter != size) {
		cacheLines[counter] = line;
		getLRU(counter++);
		return 0;
	}
	else if(replaceLine(line)) {
		return 2;
	}
	else {
		return 0;
	}
}

