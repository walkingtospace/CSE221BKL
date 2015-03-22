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

//debugging variable
#define DEBUG

//pmu functions
data_t get_overhead();
void pmcr_init();

//measurement functions
data_t memory_RAM_access();
data_t memory_latency(data_t);
data_t memory_RAM_bandwidth();
data_t pagefault_test(data_t ccnt_overhead);
#endif
