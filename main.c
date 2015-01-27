#include "cpu_test.h"

int main()
{
	int i;
	unsigned task_creation_result = 0; 
	float *proccall_test_result;

	pmcr_init();

	unsigned ccnt_overhead = get_overhead();
	
	printf("Reading overhead time is : %d\n", ccnt_overhead);
	
	proccall_test_result = cpu_proccall_overhead(ccnt_overhead);
	for(i=0;i<=PROCCALL_ARG_NUM;i++){
		printf("procedure call with %d arguments: %f\n", i, proccall_test_result[i]);
	}

	task_creation_result += cpu_task_creation(ccnt_overhead);
	printf("process creation time : %d\n",task_creation_result);


	return 0;
}
