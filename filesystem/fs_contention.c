#include "fs_contention.h"
#include <sys/mman.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

const int MAX_CONTENTION = 16;
const int BLOCK_SIZE = 4096;
const int FILE_SIZE = 1024*1024*10; //10 MB TODO: check size correct

unsigned long long  global_ccnt_overhead;
double resultTemp[MAX_CONTENTION];
double minTemp[MAX_CONTENTION];
double maxTemp[MAX_CONTENTION];
double stdTemp[MAX_CONTENTION];

typedef struct FileInfo_ {
	char *name;
	int index;
} FileInfo;

void *cont_thread(void *arg) {
	unsigned int begin, end;
	int readpos = 0, runningCnt = 0;
	char buf[BLOCK_SIZE];
	unsigned int ccnt_overhead = global_ccnt_overhead;
	double resultone;
	double minone = 9999999999;
	double maxone = 0;;
	double resultsum = 0;
	double stdone = 0;
	
	FileInfo *fileinfo = (FileInfo*)arg;
	FILE *fd = fopen(fileinfo->name, "r");
	resultTemp[fileinfo->index] = 0;
	minTemp[fileinfo->index] = 99999999999;
	maxTemp[fileinfo->index] = 0;
	stdTemp[fileinfo->index] = 0;

	for (readpos = 0 ; readpos < FILE_SIZE ; readpos += BLOCK_SIZE) {
		begin = ccnt_read();
		fread(buf, 1, BLOCK_SIZE, fd);
		end = ccnt_read();

		if(end-begin < 0){

			continue;
		}
		
		resultone = (double)(end - begin) - (double)ccnt_overhead;
		resultsum += resultone;
		stdone += resultone*resultone;
		
		if(resultone < minone) {	
			minone = resultone;
		}

		if(resultone > maxone) {
			maxone = resultone;
		}

		runningCnt++;
	}

	resultsum = resultsum / runningCnt;

	fclose(fd);
	
	resultTemp[fileinfo->index] = resultsum;
	stdTemp[fileinfo->index] = stdone / runningCnt;
	minTemp[fileinfo->index] = minone;
	maxTemp[fileinfo->index] = maxone;
	
	pthread_exit((void *) 0);

	return 0;
}

void make_file(char *filename) {
	unsigned long long int i;
	FILE *fd = fopen(filename, "w");
	char buf[BLOCK_SIZE];

	memset(buf,0,BLOCK_SIZE);

	for(i = 0 ; i < FILE_SIZE ; i += BLOCK_SIZE) {
		fwrite(buf, 1, BLOCK_SIZE, fd);
	}

	fclose(fd);
}

data_t contention_test(data_t ccnt_overhead) {
	global_ccnt_overhead = (unsigned long long)ccnt_overhead;
	unsigned int begin, end;
	int threadCount;
	double result[MAX_CONTENTION];
	double min[MAX_CONTENTION];
	double max[MAX_CONTENTION];
	double std[MAX_CONTENTION];
	int i, j, k;

	FileInfo fileinfo[MAX_CONTENTION];

	for (i = 0 ; i < MAX_CONTENTION ; i++) {
		fileinfo[i].name = (char*)malloc(32*sizeof(char));
		sprintf(fileinfo[i].name, "fscont_%d", i);
		fileinfo[i].index = i;
		make_file(fileinfo[i].name);
		
		result[i] = 0;
		min[i] = 0;
		max[i] = 0;
		std[i] = 0;

		printf("file was made: %s\n", fileinfo[i].name);
	}

	for (i = 0 ; i < MAX_CONTENTION ; i++) {
		for(j = 0 ; j < MAX_CONTENTION ; j++) {
			resultTemp[j] = 0;
		}

		threadCount = i + 1;
		
		for(k = 0 ; k < FS_CONT_NUM ; k++) {
			system("echo 3 > /proc/sys/vm/drop_caches\n");
			
			pthread_t* pthreads = (pthread_t*)malloc(sizeof(pthread_t)*threadCount);

			for(j=0 ; j < threadCount ; j++) {
				pthread_create(&pthreads[j],NULL, &cont_thread, (void *)&(fileinfo[j]));
			}

			for(j=0 ; j < threadCount ; j++) {
				int status;
				
				pthread_join(pthreads[j], (void**) &status);
				result[i] += (double)resultTemp[j];
				min[i] += minTemp[j];
				max[i] += maxTemp[j];
				std[i] += stdTemp[j];
			}
		}

		result[i] /= (double)threadCount*(double)FS_CONT_NUM;
		min[i] /= (double)threadCount*(double)FS_CONT_NUM;
		max[i] /= (double)threadCount*(double)FS_CONT_NUM;
		std[i] /= (double)threadCount*(double)FS_CONT_NUM;

		printf("%dth contention test finished: %f, %f, %f, %f\n", i, result[i], min[i], max[i], std[i]);
	}

	for (i = 0 ; i < MAX_CONTENTION ; i++) {
		printf("Contention#\d : %f cycles\n", i, result[i]);
	}
}
