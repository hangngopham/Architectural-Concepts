#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>
#include<pthread.h>

long totalSum = 0;

typedef struct args {
	int* arr;
	int size;
	int subSize;
	int index; 
	unsigned int step;
} args;

/*
Allocate space for a one dimensional integer array with size elemnts in it. 
If mode is 0, the value in the array elements are initialized with the value 
of their index. If the mode is 1, the values are initialized with random 
values between -1000 and 1000 (inclusive)
*/
int* initializeArray(unsigned int size, unsigned int mode) {
	int *arr = malloc(sizeof(int) * size);
	int i,j;
	if(mode == 0) {
		for(i = 0; i < size; i++) {
			arr[i] = i;
		}
	}
	else if(mode == 1) {
		for(j = 0; j < size; j++) {
			arr[j] = rand()%2001-1000;
		}
	}
	/*else {
		printf("Illegal value of mode. The array cannot be initialized\n");
		exit(-1);
	}*/

	return arr;
}

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void* sumBlocks(void * x) {
	long j = 0;
	struct args * block = (struct args *) x;
	int k = 0;
	unsigned long sum = 0;


	for(j = block->index;(j < block->size) && (j < (block->subSize+block->index)); j++){
		sum = sum + block->arr[j];
		printf("arr[j] j %d %d\n", j,block->arr[j]);
	}
	
	pthread_mutex_lock(&mutex1);
	printf("Sum: %d\n",sum);
	totalSum = totalSum + sum;
	printf("Total sum: %d\n",totalSum);

	pthread_mutex_unlock(&mutex1);


}

double sumArray(int* array, unsigned int size, long* sum, unsigned int numBlocks, unsigned int step) {
		int subSize; 
		subSize = size/numBlocks; 

		double elapsed;

		struct timespec start, stop;
		clock_gettime(CLOCK_REALTIME, &start);
	
		struct args thread_args[numBlocks+1];
		pthread_t threads[numBlocks+1];
		int rc,counter = 0;
		int index = 0;

		for(counter = 0; counter < numBlocks+1; counter++,index +=subSize) {
			thread_args[counter].arr = array;
			thread_args[counter].size = size;
			thread_args[counter].subSize = subSize;
			thread_args[counter].index = index;
			thread_args[counter].step = step;
			rc = pthread_create(&threads[counter],NULL,sumBlocks,(void *)&thread_args[counter]);
		}

		for(counter = 0; counter < numBlocks; counter++) {
			pthread_join(threads[counter],NULL);
			
		}
	
		clock_gettime(CLOCK_REALTIME, &stop);
		elapsed = ((double)stop.tv_sec - (double)start.tv_sec)*1000 + ((double)stop.tv_nsec - (double)start.tv_nsec)/1000000;
	
		return elapsed;
	
}

/*
Sum size randomly accessed elements in the array.

Return the number of milliseconds (ms) that the computation of 
the sum of the array takes.
*/
double sumArrayRandom(int* array, unsigned int size, int* sum) {
	int i;

	double elapsed;

	struct timespec start, stop;
	clock_gettime(CLOCK_REALTIME, &start);

	for(i = 0; i < size; i++) {
		*sum = *sum + array[rand()%size];
	}
	
	clock_gettime(CLOCK_REALTIME, &stop);
	elapsed = ((double)stop.tv_sec - (double)start.tv_sec)*1000 + ((double)stop.tv_nsec - (double)start.tv_nsec)/1000000;
	
	return elapsed;
}

/*
Check whether the character is a number or not.

Return true if the input character is a number.
Return false if the input character is not a number.
*/
bool isNumber(char *input) {
	int c = 0;
        for (c = 0; input[c] != '\0'; c++){
		if (isalpha(input[c])) {
		    return false;
		}
	}
	return true;
}

int main(int argc, char *argv[]) {
	// Default values for size, mode, blocks, steps
	int size = 10000;
	int mode = 0;
	int blocks = 1;
	int steps = 1;
	int i = 0;

	while(i < argc) {
		// -s #: Select the array size to be # elements. 
		if(strcmp(argv[i],"-s") == 0) {
			if(argv[i+1] == NULL) {
				printf("No argument after -s. Reset to default size %d.\n",10000);
			}
			else if(!isNumber(argv[i+1])) {
				printf("Not a number. Reset to default size %d.\n",10000);
			}
			else if(atoi(argv[i+1]) < 0) {
				printf("Negative number not allowed. Reset to default size %d.\n",10000);
			}
			else {
				size = atoi(argv[++i]);
			}

		}
		// -m #: Select the array initilization mode to be #. 
		// Legal values of # are only 0 and 1. 
		else if(strcmp(argv[i],"-m") == 0) {
			if(argv[i+1] == NULL) {
				printf("No argument after -m. Reset to default mode %d.\n",mode);
			}
			else if(!isNumber(argv[i+1])) {
				printf("Not a number. Reset to default mode %d.\n",mode);
			}
			else if(atoi(argv[i+1]) != 0 && atoi(argv[i+1]) != 1) {
				printf("Not legal value of mode.\n");
				exit(-1);
			}
			else {
				mode = atoi(argv[++i]);
			}
		}
		// -b #: Select the number of blocks to be #. 
		// Default is 1. Negative values are not allowed.
		else if(strcmp(argv[i],"-b") == 0) {
			if(argv[i+1] == NULL) {
				printf("No argument after -b. Reset to default blocks %d.\n",blocks);
			}
			else if(!isNumber(argv[i+1])) {
				printf("Not a number. Reset to default blocks %d.\n",blocks);
			}
			else if(atoi(argv[i+1]) < 0) {
				printf("Negative number of blocks is not allowed.\n");
				exit(-1);
			}
			else {
				blocks = atoi(argv[++i]);
			}
		}
		// -p #: Select the number of step size to be #. 
		// Default is 1. Negative values are not allowed.
		else if(strcmp(argv[i],"-p") == 0) {
			if(argv[i+1] == NULL) {
				printf("No argument after -p. Reset to default steps %d.\n",steps);
			}
			else if(!isNumber(argv[i+1])) {
				printf("Not a number. Reset to default steps %d.\n",steps);
			}
			else if(atoi(argv[i+1]) < 0) {
				printf("Negative number of steps is not allowed.\n");
				exit(-1);
			}
			else {
				steps = atoi(argv[++i]);
			}

		}
		// -r #: Select the random number seed. 
		else if(strcmp(argv[i],"-r") == 0) {
			if(argv[i+1] == NULL) {
				printf("No argument after -r. No random seed generated.\n");
			}
			else if(!isNumber(argv[i+1])) {
				printf("Not a number for random seed\n");
			}
			else  {
				srand(atoi(argv[++i]));
			}
		}
	
		i++;
	}		

	int* arr = initializeArray(size,mode);

	long s1;
	int s2;
	double time1 = sumArray(arr,size,&s1,blocks,steps);
	double time2 = sumArrayRandom(arr,size,&s2); 
	
	printf("blocks: %d\n",blocks);
	printf("size: %d\n",size);
	printf("steps: %d\n",steps);
	printf("mode: %d\n",mode);
	printf("Total sum is %d\n",totalSum);
	printf("Total time for computation of sumArray is       %f milliseconds\n",time1);
	printf("Total time for computation of sumArrayRandom is %f milliseconds\n",time2);


	return (0);
}






























