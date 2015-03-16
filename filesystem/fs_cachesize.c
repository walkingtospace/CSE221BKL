#include "cpu_test.h"
#include <sched.h>
#include <cmath>
#include <limits.h>
#include <float.h>

#define TRIAL 100
#define MB 1048576
#define BLOCK 4096
#define SECOND_PER_CYCLE 0.00000000143 

void file_cache(data_t overhead, int size) {
	data_t start1, end1;
	FILE *ptr;
	char* fullbuffer;
	float mean = 0, std = 0, min = 99999999, max = -1, median = 0;
	float result[TRIAL];
	int overflow_cnt = 0, normal_cnt = 0;	
	
	fullbuffer = (char *)malloc(size*MB);

	if(size == 50) {
		ptr = fopen("50M.input","rb");
	} else if(size == 60) {
		ptr = fopen("60M.input","rb");
	} else if(size == 70) {
		ptr = fopen("70M.input","rb");
	} else if(size == 80) {
		ptr = fopen("80M.input","rb");
	} else if(size == 90) {
		ptr = fopen("90M.input","rb");
	} else if(size == 100) {
		ptr = fopen("100M.input","rb");
	} else if(size == 110) {
		ptr = fopen("110M.input","rb");
	}  else if(size == 120) {
		ptr = fopen("120M.input","rb");
	} else if(size == 130) {
		ptr = fopen("130M.input","rb");
	} else if(size == 140) {
		ptr = fopen("140M.input","rb");
	} else if(size == 150) {
		ptr = fopen("150M.input","rb");
	} else if(size == 160) {
		ptr = fopen("160M.input","rb");
	} else if(size == 170) {
		ptr = fopen("170M.input","rb");
	} else if(size == 180) {
		ptr = fopen("180M.input","rb");
	} else if(size == 190) {
		ptr = fopen("190M.input","rb");
	} else if(size == 200) {
		ptr = fopen("200M.input","rb");
	} else if(size == 210) {
		ptr = fopen("210M.input","rb");
	} else if(size == 220) {
		ptr = fopen("220M.input","rb");
	} else if(size == 230) {
		ptr = fopen("230M.input","rb");
	} else if(size == 240) {
		ptr = fopen("240M.input","rb");
	} else if(size == 250) {
		ptr = fopen("250M.input","rb");
	} else if(size == 300) {
		ptr = fopen("300M.input","rb");
	} else if(size == 350) {
		ptr = fopen("350M.input","rb");
	} else if(size == 400) {
		ptr = fopen("400M.input","rb");
	} else if(size == 500) {
		ptr = fopen("500M.input","rb");
	} 

	for(int i = 0; i < TRIAL ; ++i) {	
		start1 = ccnt_read();
		fread(fullbuffer, sizeof(char)*MB, size, ptr);//read block size : 1MB
		end1 = ccnt_read();		
		
		float temp = end1-start1-overhead;
		
		if(temp < 0) {
			printf("%f\n",temp);
			printf("negative!\n");
			overflow_cnt++;
		} else {
			mean += temp;
			result[normal_cnt++] = temp;
			
			if(min > temp) min = temp;
			if(max < temp) max = temp;
		}

		fseek(ptr,0,SEEK_SET);
	}

	printf("the number of normal: %d\n", normal_cnt);

	mean /= (normal_cnt);

	//sorting in ASC
	for(int i = 0; i < normal_cnt ; ++i) {
		for(int j = i ; j < normal_cnt ; ++j) {
			if(result[i] > result[j]) {
				float temp = result[i];
				result[i] = result[j];
				result[j] = temp;
			}
		}
		std += pow((result[i] - mean), 2);
	}

	median = result[(normal_cnt) / 2];
	std /= (normal_cnt);

	printf("mean: %f \n", mean*SECOND_PER_CYCLE);
	printf("min: %f \n", min*SECOND_PER_CYCLE);
	printf("max: %f \n", max*SECOND_PER_CYCLE);
	printf("med: %f \n", median*SECOND_PER_CYCLE);
	printf("std: %f \n", sqrt(std));
}	
