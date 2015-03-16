#include "net_test.h"
#include <netdb.h>

void error(const char *msg) {
	perror(msg);

	exit(0);
}

data_t peakbandwidth_client(data_t ccnt_overhead, char const * servername) {
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	data_t start, end;
	float total = 0.0;
	float avg = 0.0;
	float stddev = 0.0;
	float max = 0.0; 
	float min = 10000000.0;
	char buffer[WINDOWSIZE];
	
	portno = SOCKETNO;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (sockfd < 0) {
	   	error("ERROR opening socket");
	}

	server = gethostbyname(servername);
	
	if (server == NULL) {
	   fprintf(stderr,"ERROR, no such host\n");
	
	   exit(0);
	}
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	
	bcopy((char *)server->h_addr,  (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);
	
	if (connect(sockfd, (struct sockaddr *) & serv_addr, sizeof(serv_addr)) < 0) {
	   	error("ERROR connecting");
	}  

	bzero(buffer, WINDOWSIZE);
	srand((long) time(NULL));

	for (int i = 0; i < WINDOWSIZE-1; i++) {
		buffer[i] = (char) rand() + 1;
	}

	printf("Responding...");
	for(int i = 0; i < SEND_COUNT ; i++) {
		printf("\r");
		
		if(i != 0) {
			sleep(1);
		}

		start = ccnt_read();
		n = write(sockfd,buffer,strlen(buffer));
		
		if (n < 0) {
			error("ERROR writing to socket");
		} 

		n = read(sockfd,buffer,WINDOWSIZE-1);
		if (n < 0) {
			error("ERROR reading from socket");
		}

		end = ccnt_read();
		printf("Message returned. %d", i);

		float latency = (end-start) - ccnt_overhead ;
		float prev_avg = avg;
		unsigned int k = i + 1;
		
		total += latency;
		avg += (latency - avg) / k;
		stddev += ((float) (k-1))/k * (latency - prev_avg) * (latency - prev_avg);
		
		if(latency > max) { 
			max = latency; 
		}
		
		if(latency < min) { 
			min = latency; 
		}
	}

	printf("\n");
	stddev = sqrt(stddev/SEND_COUNT);
	printf("Total: %f\t Average Send Time: %f\t Max: %f\t Min: %f\t Std. Dev: %f\n", total, avg, max, min, stddev);
	
	close(sockfd);
	
	return total;
}

data_t peakbandwidth(data_t ccnt_overhead) {
	float avg = 0.0;
	float stddev = 0.0;
	float max = 0.0; 
	float min = 1000000000.0;

	printf("Local test\n");
	for(int i = 0; i < TRIAL_COUNT ; i++) {
		unsigned int k;
		float latency, prev_avg;	

		printf("Trial %d\n", (i+1));

		//Give time for server to setup.
		if(i != 0) {
			
			sleep(10);
		}

		latency = peakbandwidth_client(ccnt_overhead, "localhost");
		
		if(latency < 0) { 
		
			continue; 
		}
		
		prev_avg = avg;
		k = i + 1;
		avg += (latency - avg) / k;
		stddev += ((float) (k-1))/k * (latency - prev_avg) * (latency - prev_avg);
		
		if(latency > max) {
			max = latency;
		}
		
		if(latency < min) {
			min = latency;
		}
		
		printf("Cumulative Average Send Time: %f\t Max: %f\t Min: %f\t Std. Dev: %f\n", avg, max, min, stddev);
		printf("======================================================================\n");
	}

	stddev = sqrt(stddev/TRIAL_COUNT);
	printf("Average Send Time: %f\t Max: %f\t Min: %f\t Std. Dev: %f\n", avg, max, min, stddev);

	//Remote
	avg = 0.0;
	stddev = 0.0;
	max = 0.0; 
	min = 1000000000.0;
	
	printf("Remote test\n");
	
	for(int i = 0 ; i < TRIAL_COUNT ; i++) {
		float prev_avg, latency;
		unsigned int k;

		printf("Trial %d\n", (i+1));
		
		//Give time for server to setup.
		if(i != 0) {
			sleep(5);
		}

		latency = peakbandwidth_client(ccnt_overhead, SERVER_IP);
		
		if(latency < 0) { 

			continue; 
		}
		
		prev_avg = avg;
		k = i + 1;
		
		avg += (latency - avg) / k;
		stddev += ((float) (k-1))/k * (latency - prev_avg) * (latency - prev_avg);
		
		if(latency > max) { 
			max = latency; 
		}
		
		if(latency < min) { 
			min = latency; 
		}
		
		printf("Cumulative Average Send Time: %f\t Max: %f\t Min: %f\t Std. Dev: %f\n", avg, max, min, stddev);
		printf("======================================================================\n");
	}

	stddev = sqrt(stddev/TRIAL_COUNT);
	printf("Average Send Time: %f\t Max: %f\t Min: %f\t Std. Dev: %f\n", avg, max, min, stddev);

	return avg;
}