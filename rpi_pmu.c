#include "cpu_test.h"
#include "stdio.h"


void pmcr_init(){
	unsigned pmcr_result;
	pmcr_result = ARMV6_PMCR_ENABLE |
			ARMV6_PMCR_CCOUNT_RESET |
			ARMV6_PMCR_CCOUNT_DIV |
			ARMV6_PMCR_CTR01_RESET;
	pmcr_write(pmcr_result);
}

data_t get_overhead(){
	int i=0;
	unsigned start, end;
	data_t total = 0;

	for(i=0; i<OVERHEAD_TEST_NUM; i++){
		start = ccnt_read();
		end = ccnt_read();
		total += (data_t)(end - start);
#ifdef DEBUG
		printf("%dth measurement overhead: %d\n",i, end - start);
#endif
	}
#ifdef DEBUG
	printf("Avg measurement overhead: %f\n", (float)total/OVERHEAD_TEST_NUM);
#endif

	return (total/OVERHEAD_TEST_NUM);
}

