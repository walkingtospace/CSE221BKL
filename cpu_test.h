#ifndef CPU_TEST_H_
#define CPU_TEST_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

#include "parameter.h"

#include "./rpi_pmu.h"

//debugging variables
#define DEBUG

//constants
#define OVERHEAD_TEST_NUM 10000
#define PROCCALL_TEST_NUM 1000000000
#define TASK_CREATION_NUM 10
#define SYSCALL_TEST_NUM 10000

#define PROCCALL_ARG_NUM 7

//pmu functions
data_t get_overhead();
void pmcr_init();

//measurement functions
data_t cpu_task_creation(data_t);
data_t* cpu_proccall_overhead(data_t ccnt_overhead);
data_t cpu_syscall_overhead(data_t ccnt_overhead);
/*
void cpu_context_switching();
void memory_RAM_access();
void memory_RAM_bandwidth();
void memory_Page_fault();
void network_roundtrip();
void network_peakbandwidth();
void network_connection_overhead();
*/


#endif
