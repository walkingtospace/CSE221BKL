#ifndef CPU_TEST_H_
#define CPU_TEST_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

#include "./rpi_pmu.h"

//constants
#define OVERHEAD_TEST_NUM 100
#define TASK_CREATION_NUM 10

//pmu functions
unsigned get_overhead();
void pmcr_init();
inline unsigned ccnt_read();
inline unsigned pmcr_read();


//measurement functions
unsigned cpu_task_creation(unsigned);
/*
void cpu_procedure_overhead();
void cpu_systemcall_overhead();
void cpu_context_switching();
void memory_RAM_access();
void memory_RAM_bandwidth();
void memory_Page_fault();
void network_roundtrip();
void network_peakbandwidth();
void network_connection_overhead();
*/


#endif
