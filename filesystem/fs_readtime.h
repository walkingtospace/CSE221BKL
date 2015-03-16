#ifndef NET_TEST_H_
#define NET_TEST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "parameter.h"
#include "rpi_pmu.h"

//debugging variable
#define DEBUG

//constants
#define FILENAME "test_files/%dK.img"
#define REMOTE_FILENAME "remote_test_files/%dK.img"

//pmu functions
data_t get_overhead();
void pmcr_init();

//measurement functions
data_t readtime(data_t, unsigned int, bool, bool);
#endif

