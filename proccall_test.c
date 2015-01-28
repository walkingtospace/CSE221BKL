#include "cpu_test.h"

void dummy_proc_0(){
	return;
}
void dummy_proc_1(int a0){
	return;
}
void dummy_proc_2(int a0, int a1){
	return;
}
void dummy_proc_3(int a0, int a1, int a2){
	return;
}
void dummy_proc_4(int a0, int a1, int a2, int a3){
	return;
}
void dummy_proc_5(int a0, int a1, int a2, int a3, int a4){
	return;
}
void dummy_proc_6(int a0, int a1, int a2, int a3, int a4, int a5){
	return;
}
void dummy_proc_7(int a0, int a1, int a2, int a3, int a4, int a5, int a6){
	return;
}

data_t* cpu_proccall_overhead(data_t ccnt_overhead)
{
	unsigned start, end;
	static data_t total[PROCCALL_ARG_NUM+1];
	int a0,a1,a2,a3,a4,a5,a6;
	a0 = 0;
	a1 = 1;
	a2 = 2;
	a3 = 3;
	a4 = 4;
	a5 = 5;
	a6 = 6;
	int i;

	for(i=0;i<=PROCCALL_ARG_NUM;i++){
		total[i] = 0;
	}
	
	for(i=0;i<PROCCALL_TEST_NUM;i++){
		start = ccnt_read();
		dummy_proc_0();
		end = ccnt_read();
		total[0] += (data_t)(end - start - ccnt_overhead);
	}

	for(i=0;i<PROCCALL_TEST_NUM;i++){
		start = ccnt_read();
		dummy_proc_1(a0);
		end = ccnt_read();
		total[1] += (data_t)(end - start - ccnt_overhead);
	}

	for(i=0;i<PROCCALL_TEST_NUM;i++){
		start = ccnt_read();
		dummy_proc_2(a0,a1);
		end = ccnt_read();
		total[2] += (data_t)(end - start - ccnt_overhead);
	}

	for(i=0;i<PROCCALL_TEST_NUM;i++){
		start = ccnt_read();
		dummy_proc_3(a0,a1,a2);
		end = ccnt_read();
		total[3] += (data_t)(end - start - ccnt_overhead);
	}

	for(i=0;i<PROCCALL_TEST_NUM;i++){
		start = ccnt_read();
		dummy_proc_4(a0,a1,a2,a3);
		end = ccnt_read();
		total[4] += (data_t)(end - start - ccnt_overhead);
	}

	for(i=0;i<PROCCALL_TEST_NUM;i++){
		start = ccnt_read();
		dummy_proc_5(a0,a1,a2,a3,a4);
		end = ccnt_read();
		total[5] += (data_t)(end - start - ccnt_overhead);
	}

	for(i=0;i<PROCCALL_TEST_NUM;i++){
		start = ccnt_read();
		dummy_proc_6(a0,a1,a2,a3,a4,a5);
		end = ccnt_read();
		total[6] += (data_t)(end - start - ccnt_overhead);
	}

	for(i=0;i<PROCCALL_TEST_NUM;i++){
		start = ccnt_read();
		dummy_proc_7(a0,a1,a2,a3,a4,a5,a6);
		end = ccnt_read();
		total[7] += (data_t)(end - start - ccnt_overhead);
	}

	for(i=0;i<=PROCCALL_ARG_NUM;i++){
		total[i] /= (float)PROCCALL_TEST_NUM;
	}

	return total;
}

