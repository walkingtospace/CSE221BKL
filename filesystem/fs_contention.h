#ifndef MEM_TEST_H_
#define MEM_TEST_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sched.h>

#include "parameter.h"
#include "rpi_pmu.h"

//debugging variables
#define DEBUG

//constants
#define FS_CONT_NUM 100

//pmu functions
data_t get_overhead();
void pmcr_init();

//measurement function
data_t contention_test(data_t ccnt_overhead);
#endif
