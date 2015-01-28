#include "cpu_test.h"

int main()
{
	int i,j;
	data_t task_creation_result = 0; 
	data_t*proccall_test_result;
	data_t syscall_test_result;

	pmcr_init();

	//Measurement overhead
	data_t ccnt_overhead;
	ccnt_overhead = get_overhead();
	printf("Reading overhead time is : %f\n", ccnt_overhead);
	
	//Procedure call test
	data_t proccall_test_temp[PROCCALL_ARG_NUM+1];
	for(i=0;i<10000;i++){
		proccall_test_result = cpu_proccall_overhead(ccnt_overhead);
		for(j=0;j<=PROCCALL_ARG_NUM;j++){
			proccall_test_temp[j] += proccall_test_result[j];
		}
#ifdef DEBUG
		for(j=0;j<=PROCCALL_ARG_NUM;j++){
			printf("%d: %f\t", j, (float)proccall_test_result[j]);
		}
		printf("\n");
#endif
	}
	for(i=0;i<=PROCCALL_ARG_NUM;i++){
		printf("procedure call with %d arguments: %f\n", i, proccall_test_temp[i]/10000);
	}

	//System call test
	syscall_test_result = cpu_syscall_overhead(ccnt_overhead);
	printf("system call overhead time : %f\n",(float)syscall_test_result);

	//Task creation test
	task_creation_result += cpu_task_creation(ccnt_overhead);
	printf("process creation time : %f\n",(float)task_creation_result);



	return 0;
}
