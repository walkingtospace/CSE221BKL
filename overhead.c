#include "rpi_pmu.h"
#include "cpu_test.h"

unsigned overhead_test(){
	int i=0;
	unsigned start, end;
	unsigned total = 0;

	//for(i=0; i < OVERHEAD_TEST_NUM; i++){
	//for(i=0; i<OVERHEAD_TEST_NUM; i++){

	//TODO: Above style cannot be compiled. Don't know the reason
	for(i=0; i<100; i++){
		start = ccnt_read();
		end = ccnt_read();
		total += end - start;
	}
	return total/OVERHEAD_TEST_NUM;
}
