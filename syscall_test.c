#include "cpu_test.h"

#include <syscall.h>
#include <unistd.h>
#include <sys/types.h>

data_t cpu_syscall_overhead(data_t ccnt_overhead){
	unsigned start, end;
	data_t total = 0;
	int i;

	for(i=0;i<SYSCALL_TEST_NUM;i++){
		start = ccnt_read();
		syscall(SYS_getpid);
		end = ccnt_read();
		total += (data_t)(end - start - ccnt_overhead);
	}

	return total/SYSCALL_TEST_NUM;
}

