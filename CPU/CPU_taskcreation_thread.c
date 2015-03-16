#include "cpu_test.h"
#include <sched.h>

#define STACK_SIZE 1024
#define THREAD_MAX_NUM 5

int void_func(void *arg) {

	return 1;
}

data_t cpu_thread_creation(data_t overhead) {
	void *child_stack = malloc(STACK_SIZE);
	unsigned start, end;
	data_t total = 0;
	int i = 0;
	pid_t pid;
		
	for(i = 0 ; i < THREAD_MAX_NUM ; ++i) {
		start = ccnt_read();
		pid = clone(&void_func,(char*)child_stack+STACK_SIZE, CLONE_THREAD|CLONE_SIGHAND|CLONE_FS|CLONE_VM|CLONE_FILES, NULL);
		end = ccnt_read();
	
		waitpid(pid, 0, 0); //wait for children
		
		if(pid == -1) {
			printf("Error in waitpid()\n");
		}
		
		total += (end - start - overhead);
	}
 
	free(child_stack);

	return total/THREAD_MAX_NUM;
}