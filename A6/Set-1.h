#ifndef SET_H
#define SET_H
#include<iostream>
#include<string>

using namespace std;

class Set {
	private:
		int size, counter, num;
		struct cacheLine{
			bool v; // valid bit
			bool d; // dirty bit
			unsigned int tag;
			int lru; 
		};
		cacheLine* cacheLines;

	public:
		Set(int);
		void getLRU(int);
		bool replaceLine(cacheLine);
		int check(unsigned int, bool);
};

#endif
