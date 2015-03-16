#include "cpu_test.h"

#include <syscall.h>
#include <unistd.h>
#include <sys/types.h>

data_t cpu_syscall_overhead(data_t ccnt_overhead){
	unsigned start, end;
	data_t total = 0;
	int i;

	data_t result_temp;
	data_t min = 9999999999;
	data_t max = 0;
	data_t std = 0;

	for(i=0;i<SYSCALL_TEST_NUM;i++){
		start = ccnt_read();
		syscall(SYS_getpid);
		end = ccnt_read();
		if(end-start<0){
			i-=-1;
			continue;
		}	
		result_temp = (data_t)(end-start)-ccnt_overhead;
		total += result_temp;
		if(min>result_temp)
			min = result_temp;
		if(max<result_temp)
			max = result_temp;
		std += result_temp*result_temp;
	}
	total = total / SYSCALL_TEST_NUM;
	std = std/SYSCALL_TEST_NUM - total*total;
	printf("System call overhead///\n");
	printf("Avg: %f\n", total);
	printf("Max: %f\n", max);
	printf("Min: %f\n", min);
	printf("Std: %f\n", std);

	return total/SYSCALL_TEST_NUM;
}
