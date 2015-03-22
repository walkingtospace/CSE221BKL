#include "mem_latency.h"
#include <time.h>
#include <math.h>
#include <memory.h>

static const unsigned int LATENCY_ACCESS_TRIALS = 100000000;
static const size_t INT_SIZE = sizeof(int);
static const unsigned int STRIDE_TRIALS = 10;
static const unsigned int STRIDE_START = 128;

//256B
static const size_t array_size0 = 256;
//512B
static const size_t array_size1 = 256*2;
//1KB
static const size_t array_size2 = 256*4;
//2KB
static const size_t array_size3 = 256*8;
//4KB
static const size_t array_size4 = 256*16;
//8KB
static const size_t array_size5 = 256*32;
//16KB
static const size_t array_size6 = 256*64;
//32KB
static const size_t array_size7 = 256*128;
//64KB
static const size_t array_size8 = 256*256;
//128KB
static const size_t array_size9 = 256*512;
//256KB
static const size_t array_size10 = 256*1024;
//512KB
static const size_t array_size11 = 256*2048;
//1MB
static const size_t array_size12 = 256*4096;
//2MB
static const size_t array_size13 = 256*8192;
//4MB
static const size_t array_size14 = 256*16384;
//8MB
static const size_t array_size15 = 256*32768;
//16MB
static const size_t array_size16 = 256*65536;
//32MB
static const size_t array_size17 = 256*pow(2,17);
//64MB
static const size_t array_size18 = 256*pow(2,18);

data_t memory_latency_helper(data_t, size_t, unsigned int);
void make_cyclic_array(int *, size_t, unsigned int);
unsigned int uniform_rand(unsigned int);

data_t memory_latency(data_t ccnt_overhead) {
	for(unsigned int i = 0 ; i < STRIDE_TRIALS ; i++) {
		unsigned int stride = STRIDE_START * pow(2,i) + 1;

		printf("Trial #%u, Stride size: %u\n", i, stride);
		
		memory_latency_helper(ccnt_overhead, array_size0, stride);
		memory_latency_helper(ccnt_overhead, array_size1, stride);
		memory_latency_helper(ccnt_overhead, array_size2, stride);
		memory_latency_helper(ccnt_overhead, array_size3, stride);
		memory_latency_helper(ccnt_overhead, array_size4, stride);
		memory_latency_helper(ccnt_overhead, array_size5, stride);
		memory_latency_helper(ccnt_overhead, array_size6, stride);
		memory_latency_helper(ccnt_overhead, array_size7, stride);
		memory_latency_helper(ccnt_overhead, array_size8, stride);
		memory_latency_helper(ccnt_overhead, array_size9, stride);
		memory_latency_helper(ccnt_overhead, array_size10, stride);
		memory_latency_helper(ccnt_overhead, array_size11, stride);
		memory_latency_helper(ccnt_overhead, array_size12, stride);
		memory_latency_helper(ccnt_overhead, array_size13, stride);
		memory_latency_helper(ccnt_overhead, array_size14, stride);
		memory_latency_helper(ccnt_overhead, array_size15, stride);
		memory_latency_helper(ccnt_overhead, array_size16, stride);
		memory_latency_helper(ccnt_overhead, array_size17, stride);
		memory_latency_helper(ccnt_overhead, array_size18, stride);
	}

	return 0;
}

data_t memory_latency_helper(data_t ccnt_overhead, size_t size, unsigned int stride) {
	unsigned start, end;
	float avg = 0.0;
	float stddev = 0.0;
	float max = 0.0; 
    	float min = 10000.0;
	int * array = (int *) malloc((size_t) size);
	
	if(array == NULL) {
		printf("Malloc error!\n");
		
		exit(1);
	}

	memset(array, 1, size);
	make_cyclic_array(array, size, stride);

	int * cur = array;
	for(unsigned int i = 0; i < LATENCY_ACCESS_TRIALS; i++) {
		start = ccnt_read();
		cur = (int *) *cur;
		end = ccnt_read();

		float latency = (end-start) - ccnt_overhead ;
		float prev_avg = avg;
		unsigned int k = i + 1;
		
		avg += (latency - avg) / k;
		stddev += ((float) (k-1))/k * (latency - prev_avg) * (latency - prev_avg);
		
		if(latency > max) { 
			max = latency; 
		}

		if(latency < min) { 
			min = latency; 
		}
	}

	stddev = sqrt(stddev);
	printf("Size: %u\t Average Access Time: %f\t Max: %f\t Min: %f\t Std. Dev: %f\n", size, avg, max, min, stddev);
	
	free(array);
	
	return 0;
}

void make_cyclic_array(int * array, size_t size, unsigned int stride) {
	void ** ptrarray =  (void **) array;
	unsigned int arraysize = size / sizeof(int *);
	unsigned int stridesize = stride / sizeof(int *);

	for (unsigned int i = 0; i < arraysize; i++) {
		ptrarray[i] = &ptrarray[(i + stridesize) % arraysize];
	}
}

unsigned int uniform_rand(unsigned int range) {
    double myRand = rand() / (1.0 + RAND_MAX); 
	unsigned int myRand_scaled = myRand * (range + 1);
	
	return myRand_scaled;
}

