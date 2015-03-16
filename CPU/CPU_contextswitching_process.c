#include "cpu_test.h"
#include <sched.h>

data_t cpu_cs_process(data_t overhead) {
	unsigned start, end;
	pid_t childPID;
	int i, fd[2];
	data_t total = 0;
	char buf;

	if(pipe(fd)) {
		printf("pipe() is failed\n");

		return 0;
	}

	for(i = 0 ; i < TASK_CREATION_NUM ; ++i) {
		childPID = fork();
		
		if(childPID < 0) {
			printf("fork() was failed\n");
		} else if(childPID > 0) { //parent
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

			_exit(EXIT_SUCCESS);
		}
		
		total += ((end - start)/2 - overhead);
	}
	
	printf("\n");	

	return (total/TASK_CREATION_NUM);
}