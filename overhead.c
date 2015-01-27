#include "stdio.h"

#include "rpi_pmu.h"

int main()
{
	int i=0;
	pmcr_init();
	unsigned aa[100];
	unsigned start, end;
	for(i=0;i<100;i++){
		start = ccnt_read();
		end = ccnt_read();
		aa[i] = end - start;
	}

	for(i=0;i<100;i++){
		printf("%d\n", aa[i]);
	}
}
