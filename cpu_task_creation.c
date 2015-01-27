#include "./cpu_test.h"

unsigned cpu_task_creation(unsigned overhead) {
	unsigned start, end;
	pid_t childPID;

	start = ccnt_read();
	childPID = fork();
	end = ccnt_read();
	kill(childPID, SIGKILL); //kill child\

	if(childPID >= 0) {
		//fork success 
	} else {
		printf("Fork failed. suck.\n");
	}	
	
	return ((end-start)-overhead); 
}

