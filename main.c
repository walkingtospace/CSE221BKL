#include "stdio.h"

#include "rpi_pmu.h"
#include "cpu_test.h"


void pmcr_init()
{
	unsigned pmcr_result;
	pmcr_result = ARMV6_PMCR_ENABLE |
			ARMV6_PMCR_CCOUNT_RESET |
			ARMV6_PMCR_CCOUNT_DIV |
			ARMV6_PMCR_CTR01_RESET;
	pmcr_write(pmcr_result);
}

int main()
{
	pmcr_init();

	unsigned overhead_result = overhead_test();

	printf("%d\n", overhead_result);

	return 0;
}
