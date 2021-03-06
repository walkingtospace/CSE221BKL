#include "cpu_test.h"
#include <sched.h>
#include "math.h"

#define STACK_SIZE 1024
#define THREAD_MAX_NUM 5

int void_func(void *arg) {

	return 1;
}

void cpu_thread_creation(data_t overhead) {
	void *child_stack = malloc(STACK_SIZE);
	unsigned start, end;
	data_t total = 0;
	int i = 0;
	pid_t pid;
	float mean = 0, std = 0, min = 99999999, max = 0, median = 0;
	float result[THREAD_MAX_NUM];	
		
	for(i=0 ; i<THREAD_MAX_NUM ; ++i) {
		start = ccnt_read();
		pid = clone(&void_func,(char*)child_stack+STACK_SIZE, CLONE_THREAD|CLONE_SIGHAND|CLONE_FS|CLONE_VM|CLONE_FILES, NULL);
		end = ccnt_read();
	
		waitpid(pid, 0, 0); //wait for children
		if(pid == -1) {
			printf("Error in waitpid()\n");
		}
	
		float temp = (end-start-overhead);
		if(temp < 0) printf("negative!");

		total += temp;
		result[i] = (float)temp;

		if(min > temp) {
			min = temp;
		} 	

		if(max < temp) {
			max = temp;
		}

		total += (end - start - overhead);
	}
 
	free(child_stack);

	for(int i = 0; i < THREAD_MAX_NUM ; ++i) {
		for(int j = i; j < THREAD_MAX_NUM ; ++j) {
			if(result[i] > result[j]) {
				float temp = result[i];
				result[i] = result[j];
				result[j] = temp;	
			}
		}

		std += pow((result[i] - mean), 2);
	}

	median = result[THREAD_MAX_NUM/2];
	mean = (total/THREAD_MAX_NUM);
	std /= (THREAD_MAX_NUM);	
	
	printf("mean : %f \n", mean);
	printf("median : %f \n", median);
	printf("max : %f \n", max);
	printf("min : %f \n", min);
	printf("std : %f \n", sqrt(std));
}

