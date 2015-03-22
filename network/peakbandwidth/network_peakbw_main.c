#include "net_test.h"

int main() {
	data_t peakbandwidth_result;

	pmcr_init();

	//Measurement overhead
	data_t ccnt_overhead;
	ccnt_overhead = get_overhead();
	printf("Reading overhead time is : %f\n", ccnt_overhead);
	
	peakbandwidth_result = peakbandwidth(ccnt_overhead);
	printf("%f\n", peakbandwidth_result);

	return 0;
}

