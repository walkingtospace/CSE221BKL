#include "cpu_test.h"
#include <sched.h>
#include "math.h"

void cpu_cs_process(data_t overhead) {
	unsigned start, end;
	pid_t childPID;
	int i;
	data_t total = 0;
	int fd[2];
	char buf;
	float mean = 0, std = 0, min = 99999999, max = 0, median = 0;
	float result[TASK_CREATION_NUM];	

	if(pipe(fd)) {
		printf("pipe() is failed\n");

		return ;
	}

	for(i=0; i<TASK_CREATION_NUM ; ++i) {
		childPID = fork();
		
		if(childPID < 0) {
			printf("fork() was failed\n");
		} else if(childPID > 0){ //parent
			close(fd[0]);
			write(fd[1], "t", 1); //write 1 byte		
		
			close(fd[1]);
			start = ccnt_read();
			wait(NULL);
			end = ccnt_read();
		} else if(childPID == 0) { //child
			if(i != 0 && i % 500 == 0) {
				printf(".");
				fflush(stdout);
			}

			close(fd[1]);
			while(read(fd[0], &buf, 1) > 0) { //wait until signal from the parent
				//write(STDOUT_FILENO, &buf, 1);
			}

			//write(STDOUT_FILENO, "\n", 1);
			//close(fd[0]);
			
			_exit(EXIT_SUCCESS);
		}
		
		float temp = ((end-start)/2-overhead);
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

