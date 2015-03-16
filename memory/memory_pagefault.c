#include "cpu_test.h"
#include "time.h"
#include "stdio.h"

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <memory.h>
#include <sys/stat.h>
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

const int PAGE_SIZE = 4096;
const int MAX_PAGE_NUM = 10;
const int MAX_ARR_SIZE = 4096;
const int MAX_MEM_SIZE = 512*1024*1024; //(Bytes)
const int MAX_MEM_DIV = 6;
const int INNER_ITER = 1;
const int OUTER_ITER = 100000;

data_t pagefault_test(data_t ccnt_overhead) {
	unsigned start, end;
	int fd,i, j, r, temp;
	char *file = NULL;
	int flag = PROT_WRITE | PROT_READ ;
	size_t s;
	char u;
	struct stat sbuf;
	data_t result_temp[INNER_ITER];
	data_t total_fault = 0;
	data_t total_notfault = 0;

	srand(time(NULL));

	FILE *result_file;
	result_file = fopen("./result.txt", "w");

	for(j = 0 ; j < OUTER_ITER ; j++) {
		if((fd = open("pgfault_test.txt", O_RDWR|O_CREAT|O_TRUNC|O_SYNC)) < 0) {
			printf("File open error\n");
		}

		if (stat("./result.txt", &sbuf) == -1) {
			perror("stat");
			exit(1);
		}

		ftruncate(fd,MAX_ARR_SIZE);

		if((file = (char*)mmap((caddr_t)0, MAX_ARR_SIZE, PROT_READ, MAP_SHARED ,fd,0)) == MAP_FAILED) {
			printf("mmap errono: %d\n", errno);
		}

		for(i = 0 ; i < INNER_ITER ; i++) {
			r = rand() % MAX_PAGE_NUM;
			start = ccnt_read();
			u = file[r+0];
			end = ccnt_read();

			total_fault += (data_t)(end-start-ccnt_overhead);
			result_temp[i] = (data_t)(end-start-ccnt_overhead);
		}

		for(i = 0 ; i < INNER_ITER ; i++) {
			fprintf(result_file, "%f\n", (float)(result_temp[i]));
		}

		munmap(file, MAX_ARR_SIZE);
		remove("pgfault_test.txt");

		close(fd);
	}
	
	fclose(result_file);

	printf("Result: read with page fault time: %f\n", (float)total_fault/INNER_ITER/OUTER_ITER);
}