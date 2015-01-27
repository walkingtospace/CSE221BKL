#include "./cpu_test.h"

unsigned cpu_task_creation(unsigned overhead) {
	unsigned start, end;
	pid_t childPID;
	int i;
	unsigned total = 0;

	for(i=0;i<TASK_CREATION_NUM;i++){

		start = ccnt_read();
		childPID = fork();
		end = ccnt_read();
		kill(childPID, SIGKILL); //kill child\

		//Shouldn't it be ">0" ?)
		if(childPID >= 0) {
			//fork success 
		} else {
			printf("Fork failed. suck.\n");
		}	

		total += end - start - overhead;
	}
	total /= TASK_CREATION_NUM;

	return total;
}

