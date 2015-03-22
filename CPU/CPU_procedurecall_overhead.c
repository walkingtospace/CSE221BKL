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

	data_t min[PROCCALL_ARG_NUM+1];
	data_t max[PROCCALL_ARG_NUM+1];
	data_t std[PROCCALL_ARG_NUM+1];
	data_t result_temp = 0;

	for(i=0;i<=PROCCALL_ARG_NUM;i++){
		total[i] = 0;
		min[i] = 99999999999999;
		max[i] = 0;
		std[i] = 0;
	}
	
	for(i=0;i<PROCCALL_TEST_NUM;i++){
		start = ccnt_read();
		dummy_proc_0();
		end = ccnt_read();
		if(end-start<0){
			i-=1;
			continue;
		}
		result_temp = (data_t)(end-start-ccnt_overhead);
		total[0] += result_temp;
		if(min[0]>result_temp)
			min[0] = result_temp;
		if(max[0]<result_temp)
			max[0] = result_temp;
		std[0] += result_temp*result_temp;
	}

	for(i=0;i<PROCCALL_TEST_NUM;i++){
		start = ccnt_read();
		dummy_proc_1(a0);
		end = ccnt_read();
		if(end-start<0){
			i-=1;
			continue;
		}
		result_temp = (data_t)(end-start-ccnt_overhead);
		total[1] += result_temp;
		if(min[1]>result_temp)
			min[1] = result_temp;
		if(max[1]<result_temp)
			max[1] = result_temp;
		std[1] += result_temp*result_temp;
	}

	for(i=0;i<PROCCALL_TEST_NUM;i++){
		start = ccnt_read();
		dummy_proc_2(a0,a1);
		end = ccnt_read();
		if(end-start<0){
			i-=1;
			continue;
		}
		result_temp = (data_t)(end-start-ccnt_overhead);
		total[2] += result_temp;
		if(min[2]>result_temp)
			min[2] = result_temp;
		if(max[2]<result_temp)
			max[2] = result_temp;
		std[2] += result_temp*result_temp;
	}

	for(i=0;i<PROCCALL_TEST_NUM;i++){
		start = ccnt_read();
		dummy_proc_3(a0,a1,a2);
		end = ccnt_read();
		if(end-start<0){
			i-=1;
			continue;
		}
		result_temp = (data_t)(end-start-ccnt_overhead);
		total[3] += result_temp;
		if(min[3]>result_temp)
			min[3] = result_temp;
		if(max[3]<result_temp)
			max[3] = result_temp;
		std[3] += result_temp*result_temp;
	}

	for(i=0;i<PROCCALL_TEST_NUM;i++){
		start = ccnt_read();
		dummy_proc_4(a0,a1,a2,a3);
		end = ccnt_read();
		if(end-start<0){
			i-=1;
			continue;
		}
		result_temp = (data_t)(end-start-ccnt_overhead);
		total[4] += result_temp;
		if(min[4]>result_temp)
			min[4] = result_temp;
		if(max[4]<result_temp)
			max[4] = result_temp;
		std[4] += result_temp*result_temp;
	}

	for(i=0;i<PROCCALL_TEST_NUM;i++){
		start = ccnt_read();
		dummy_proc_5(a0,a1,a2,a3,a4);
		end = ccnt_read();
		if(end-start<0){
			i-=1;
			continue;
		}
		result_temp = (data_t)(end-start-ccnt_overhead);
		total[5] += result_temp;
		if(min[5]>result_temp)
			min[5] = result_temp;
		if(max[5]<result_temp)
			max[5] = result_temp;
		std[5] += result_temp*result_temp;
	}

	for(i=0;i<PROCCALL_TEST_NUM;i++){
		start = ccnt_read();
		dummy_proc_6(a0,a1,a2,a3,a4,a5);
		end = ccnt_read();
		if(end-start<0){
			i-=1;
			continue;
		}
		result_temp = (data_t)(end-start-ccnt_overhead);
		total[6] += result_temp;
		if(min[6]>result_temp)
			min[6] = result_temp;
		if(max[6]<result_temp)
			max[6] = result_temp;
		std[6] += result_temp*result_temp;
	}

	for(i=0;i<PROCCALL_TEST_NUM;i++){
		start = ccnt_read();
		dummy_proc_7(a0,a1,a2,a3,a4,a5,a6);
		end = ccnt_read();
		if(end-start<0){
			i-=1;
			continue;
		}
		result_temp = (data_t)(end-start-ccnt_overhead);
		total[7] += result_temp;
		if(min[7]>result_temp)
			min[7] = result_temp;
		if(max[7]<result_temp)
			max[7] = result_temp;
		std[7] += result_temp*result_temp;
	}

	for(i=0;i<=PROCCALL_ARG_NUM;i++){
		total[i] /= (float)PROCCALL_TEST_NUM;
		std[i] = std[i]/(float)PROCCALL_TEST_NUM - total[i]*total[i];
	}

	printf("Procedure call overhead\n");
	for(i=0;i<=PROCCALL_ARG_NUM;i++){
		printf("Arguments number: %d\n", i);
		printf("Avg: %f\n", total[i]);
		printf("Max: %f\n", max[i]);
		printf("Min: %f\n", min[i]);
		printf("Std: %f\n", std[i]);
	}

	return total;
}

