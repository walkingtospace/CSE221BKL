#include "fs_readtime.h"
#include <float.h>

static const unsigned int FS_READ_TRIALS = 10;
static const unsigned int BLOCK_SIZE = 4;  // 4KB = Block size
static const unsigned int START_SIZE = BLOCK_SIZE;
static const unsigned int END_SIZE = 256 * 1024; // 512MB
static const unsigned int STRIDE = 2;

int main(int argc, char * argv[]) {
	data_t ccnt_overhead;
	data_t fs_read_time_result;

	pmcr_init();

	//Measurement overhead
	ccnt_overhead = get_overhead();
	printf("Reading overhead time is : %f\n", ccnt_overhead);
	
	printf("Local Sequential\n");
	for(unsigned int size = START_SIZE ; size < END_SIZE+1 ; size *= STRIDE) {
		fs_read_time_result = readtime(ccnt_overhead, size, false, false);
	}
	
	printf("Local Random\n");
	for(unsigned int size = START_SIZE ; size < END_SIZE+1 ; size *= STRIDE) {
		fs_read_time_result = readtime(ccnt_overhead, size, true, false);
	}

	printf("Remote Sequential\n");
	for(unsigned int size = START_SIZE ; size < END_SIZE+1 ; size *= STRIDE) {
		fs_read_time_result = readtime(ccnt_overhead, size, false, true);
	}
	printf("Remote Random\n");
	for(unsigned int size = START_SIZE ; size < END_SIZE+1 ; size *= STRIDE) {
		fs_read_time_result = readtime(ccnt_overhead, size, true, true);
	}

	return 0;
}

data_t readtime(data_t ccnt_overhead, unsigned int size, bool random_read, bool remote_read) {
	int fd;
	data_t start, end;
	float total = 0.0;
	float avg = 0.0;
	float stddev = 0.0;
	float max = 0.0; 
	float min = 1000000000000.0;
	char filename[32]; 
	char buf[BLOCK_SIZE * 1024];
	unsigned int i;
	unsigned int block_count = size / BLOCK_SIZE_KB;
	
	if(remote_read) {
		sprintf(filename, REMOTE_FILENAME, size);
	} else {
		sprintf(filename, FILENAME, size);
	}

	printf("%uKB: \t\t", size);
	
	for(i = 0 ; i < FS_READ_TRIALS ; i++) {
		float accum = 0.0;
		ssize_t s = 0;
		int count = 0;
		ssize_t s_tot = 0;

		system("echo 3 > /proc/sys/vm/drop_caches\n");
		if(remote_read)
		{
			mount("76.167.145.48:/remote", "./remote_test_files", "nfs", 0, "ro");
		}
		if((fd = open(filename, O_SYNC|O_DIRECT)) == -1 ) 
			printf("%s: Open error\n", filename);
			printf("%s\n", strerror(errno));
			exit(1);
		}
	
		srandom(time(NULL));
		
		do {
			if(random_read) {
				unsigned int offset = random() % (size / BLOCK_SIZE);
				
				if(lseek(fd, offset * BLOCK_SIZE * 1024, SEEK_SET) == -1) {
					printf("Seek error\n");
					printf("%s\n", strerror(errno));
					exit(1);
				}
			}

			start = ccnt_read();
			s = read(fd, buf, BLOCK_SIZE_KB * 1024);
			end = ccnt_read();
			
			s_tot += s;
			if(end-start < 0) {
				block_count--;
				continue;
			}

			accum += (end-start) - ccnt_overhead;
			count++;
		} while((unsigned int) s < size * 1024);

		float prev_avg = avg;
		unsigned int k = i + 1;
		
		total += accum;
		avg += (accum - avg) / k;
		stddev += ((float) (k-1))/k * (accum - prev_avg) * (accum - prev_avg);

		if(accum > max) { 
			max = accum; 
		}
		
		if(accum < min) { 
			min = accum; 
		}

		close(fd);
	}

	stddev = sqrt(stddev/i);

	printf("Average: %.3f\tMax: %.3f\tMin: %.3f\tStd. Dev: %.3f\tTrial Count: %d\n",
			avg, max, min, stddev, i);

	printf("Per Block\tAverage: %.3f\tMax: %.3f\tMin: %.3f\tStd. Dev: %.3f\tTrial Count: %d\n",
			avg/block_count, max/block_count, min/block_count, stddev/block_count, i);

	return avg;
}

