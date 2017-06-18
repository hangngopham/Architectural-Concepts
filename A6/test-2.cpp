#include "CacheSet.h"
#include<iostream>
#include<sstream>
#include<fstream>
#include<cstring>
#include<iomanip>
#include<cstdlib>

using namespace std;

/*Check if the number is a postive power of two. 
  Return 1 if x is a positive power of two.
  Return 0 if x is not a positive power of two.
*/
int powerOfTwo(unsigned int x) {
	while((x%2 == 0) && x > 1) {
		x = x/2;
	}
	return (x==1);
}

int main(int argc, char *argv[]) {
	int blockSize = 1;
	int cacheSize = 1024;
	int associativity = 1;
	bool writeback = true;
	char* fileName;
	int i = 1;
	while(i < argc) {
		// -b: block size
		if(strcmp(argv[i],"-b") == 0) {
			if(powerOfTwo(atoi(argv[i+1])) == 1) {
				blockSize = atoi(argv[++i]);
			}
			else {
				cout << "Invalid value of block size." << endl;
				exit(-1);
			}
		}
		else if(strcmp(argv[i],"-a") == 0) {
			if(powerOfTwo(atoi(argv[i+1])) == 1) {
				associativity = atoi(argv[++i]);
			}
			else {
				cout << "Invalid value of associativity." << endl;
				exit(-1);
			}
		}	
		// -n: cache_size
		else if(strcmp(argv[i],"-n") == 0) {
			if(powerOfTwo(atoi(argv[i+1])) == 1) {
				cacheSize = atoi(argv[++i]);
			}
			else {
				cout << "Invalid value of cache size." << endl;
				exit(-1);
			}
		}
		// -w T|B: set the write policy. T sets it to write through, B to write back.
		if(strcmp(argv[i],"-w") == 0) {
			if(strcmp(argv[i+1],"T") == 0) {
				writeback = false;
			}
			else if(strcmp(argv[i+1],"B") == 0) {
				writeback = true;
			}
		}
		// -f filename: specify what file you want to test
		else if(strcmp(argv[i],"-f") == 0) {
			fileName = argv[++i];
		}
		
		i++;
	}

	CacheSet cacheSet(cacheSize,blockSize,associativity);
	ifstream inputFile(fileName);
	string line;
	if(!inputFile) {
		cout << "Cannot open input file" << endl;
		return 1;
	}
	int total = 0;

	while(getline(inputFile,line)) {
		istringstream ss(line);
		string address, mode;
		ss >> address >> mode;
		
		char *p;
		long n = strtol(address.c_str(),&p,16);
		if(*p != 0) {
			cout << "not a number" << endl;
		}
		
		if(mode == "R") {		
			cacheSet.count_Misses_Hits(n,false);
		}
		else if(mode == "W") {
			cacheSet.count_Misses_Hits(n,true);
		}
	}
	if(writeback) {
		cacheSet.print(writeback);
	}
	else {
		cacheSet.print(!writeback);
	}
	inputFile.close();
}
