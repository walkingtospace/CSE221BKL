#include "cpu_test.h"
#include "stdio.h"

static inline void pmcr_write(unsigned long val){
	asm volatile("mcr   p15, 0, %0, c15, c12, 0" : : "r"(val));
}

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

inline unsigned ccnt_read()
{
	unsigned cc;
	asm volatile ("mrc p15, 0, %0, c15, c12, 1" : "=r" (cc));
	return cc;
}

inline unsigned pmcr_read(){
	unsigned val;
	asm volatile("mrc   p15, 0, %0, c15, c12, 0" : "=r"(val));
	return val;
}

