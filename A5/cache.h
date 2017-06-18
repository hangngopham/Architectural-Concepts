#include<iostream>
#include<string>

class Cache {
	private:
		int* cache;
		int cache_size;
		int block_size;
		int numBlocks;

		int read_hits;
		int read_misses;

		int write_hits;
		int write_misses;

		int miss_time;

		
	public:
		Cache(int,int,int);	
		unsigned int numTag(unsigned int);
		unsigned int countIndex(unsigned int);
		void count_Misses_Hits(unsigned int, bool);
		void print();
		~Cache();
		
};
