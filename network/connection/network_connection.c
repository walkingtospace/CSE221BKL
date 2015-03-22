#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

#include "cpu_test.h"
#include "parameter.h"

const char *SERVER_IP = "76.167.145.48";
const char *LOCAL_IP= "localhost";
const int PORT_ROUND_TRIP =2224;
int repeat = 0;

data_t netconn_test_implementation(const char * ip, data_t ccnt_overhead);

data_t network_connection_overhead(data_t ccnt_overhead) {
	netconn_test_implementation(SERVER_IP, ccnt_overhead);
}

data_t netconn_test_implementation(const char * ip, data_t ccnt_overhead) {
	int i, sock;
	struct hostent *h;
	struct sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr)); 
	char c;
	FILE *result_file;
	
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons(PORT_ROUND_TRIP);
	
	if(repeat == 0) {
		result_file = fopen("result_netconn_remote.txt","w");
		repeat++;
	} else {
		result_file = fopen("result_netconn_local.txt","w");
	}

	unsigned int begin, middle1, middle2, end;
	data_t teardown_ov, conn_ov;
	
	for(i = 0 ; i < NETCONN_TEST_NUM ; i++) {
		if((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
			printf("SYS: Socket error\n");

			return 0;
		}

		bind(sock, (struct sockaddr*)&sockAddr, sizeof(sockAddr));
		h = gethostbyname(ip);
		bcopy((void*)h->h_addr, (void *)&sockAddr.sin_addr, h->h_length);

		begin = ccnt_read();
		if(connect(sock, (struct sockaddr*)&sockAddr, sizeof(sockAddr))) {
			printf("SYS: Socket Error in connect\n");
		}
		middle1 = ccnt_read();

		write(sock, &c, 1);
		read(sock, &c, 1);

		middle2 = ccnt_read();
		if(close(sock)) {
			printf("SYS: Socket Error in close\n");
		}

		end = ccnt_read();

		fprintf(result_file, "%f\t%f\n", (float)((data_t)(middle1-begin) - ccnt_overhead), (float)((data_t)(end - middle2) - ccnt_overhead));
		conn_ov = (data_t)(middle1 - begin) - ccnt_overhead;	
		teardown_ov = (data_t)(end - middle2) - ccnt_overhead;	
		printf("%dth connection: %f\n",i, (float)conn_ov); 

		sleep(1);
	}

	fclose(result_file);
	
	return conn_ov;
}

