#include "fs_contention.h"

int main() {
	pmcr_init();

	//Measurement overhead
	data_t ccnt_overhead;
	ccnt_overhead = get_overhead();
	printf("Reading overhead time is : %f\n", ccnt_overhead);
	
	contention_test(ccnt_overhead);

	return 0;
}

