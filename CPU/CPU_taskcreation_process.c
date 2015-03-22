#include "./cpu_test.h"
#include <math.h>

void cpu_process_creation(data_t overhead) {
	data_t start, end;
	pid_t childPID;
	int i;
	float total = 0;
	float mean = 0, std = 0, min = 99999999, max = 0, median = 0;
	float result[TASK_CREATION_NUM];	
	
	for(i=0 ; i<TASK_CREATION_NUM ; ++i){
		start = ccnt_read();
		childPID = fork();
		end = ccnt_read();
		
		if(childPID < 0) {
			printf("fork() was failed\n");
		} else if(childPID > 0){ //parent
			wait(NULL);
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
		} else if(childPID == 0) { //child
			if(i != 0 && i % 500 == 0) {
				printf(".");
				fflush(stdout);
			}
			
			_exit(EXIT_SUCCESS);
		}
	}
	
	printf("\n");

	for(int i = 0; i < TASK_CREATION_NUM ; ++i) {
		for(int j = i; j < TASK_CREATION_NUM ; ++j) {
			if(result[i] > result[j]) {
				float temp = result[i];
				result[i] = result[j];
				result[j] = temp;	
			}
		}

		std += pow((result[i] - mean), 2);
	}

	median = result[TASK_CREATION_NUM/2];
	mean = (total/TASK_CREATION_NUM);
	std /= (TASK_CREATION_NUM);	
	
	printf("mean : %f \n", mean);
	printf("median : %f \n", median);
	printf("max : %f \n", max);
	printf("min : %f \n", min);
	printf("std : %f \n", sqrt(std));
}

