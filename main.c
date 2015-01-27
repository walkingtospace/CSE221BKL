#include "cpu_test.h"

int main()
{
	unsigned task_creation_sum = 0; 
	int i;

	pmcr_init();

	unsigned overhead_result = get_overhead();
	
	printf("Reading overhead time is : %d\n", overhead_result);
	
	for(i=0; i<TASK_CREATION_NUM ; ++i) {
		task_creation_sum += cpu_task_creation(overhead_result);
	}

	printf("process creation time : %d\n",task_creation_sum/TASK_CREATION_NUM);

	return 0;
}
