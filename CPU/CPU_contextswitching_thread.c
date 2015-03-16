#include "cpu_test.h"
#include <sched.h>

#define STACK_SIZE 1024
#define THREAD_MAX_NUM 5

int fd[2];
char buf;

int pipe_func(void *arg) {
	close(fd[1]);

	while(read(fd[0], &buf, 1) > 0) { //wait until signal from the parent
		//write(STDOUT_FILENO, &buf, 1);
	}
	
	return 0;
}

data_t cpu_cs_thread(data_t overhead) {
	void *child_stack = malloc(STACK_SIZE);
	unsigned start, end;
	data_t total = 0;
	int i = 0;
	pid_t pid;
			
	if(pipe(fd)) {
		printf("pipe() is failed\n");

		return 0;
	}

	fd[0] = -1;
	fd[1] = -1;

	for(i = 0 ; i < THREAD_MAX_NUM ; ++i) {
		pid = clone(&pipe_func,(char*)child_stack+STACK_SIZE, CLONE_THREAD|CLONE_SIGHAND|CLONE_FS|CLONE_VM|CLONE_FILES, NULL);
			
		close(fd[0]);
		write(fd[1], "t", 1); //write 1 byte		

		close(fd[1]);
		start = ccnt_read();
		waitpid(pid, 0, 0); //wait for children
		end = ccnt_read();
		
		if(pid == -1) {
			printf("Error in waitpid()\n");
		}
		
		printf("%f\n", end-start-overhead);
		total += (end - start - overhead);
	}
 
	free(child_stack);

	return total/THREAD_MAX_NUM;
}