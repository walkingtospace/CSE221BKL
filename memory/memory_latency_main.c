#include "mem_latency.h"

int main() {
	data_t memlatency_result;

	pmcr_init();

	//Measurement overhead
	data_t ccnt_overhead;
	ccnt_overhead = get_overhead();
	printf("Reading overhead time is : %f\n", ccnt_overhead);
	
	memlatency_result = memory_latency(ccnt_overhead);

	return 0;
}

