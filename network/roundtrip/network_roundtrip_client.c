#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include "cpu_test.h"
#include <math.h>

#define BUF_SIZE 1024
#define TCP_HEADER_SIZE 66
#define ICMP_HEADER_SIZE 44
#define TRIALS 100

void error(const char *msg) {
    perror(msg);

    exit(0);
}

int main(int argc, char *argv[]) {
    int sockfd, portno, wn, rn, option;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    data_t start, end;
    double result[1000];
    double total = 0, min_val = 99999999, max_val = 0,  std = 0;
    
    pmcr_init();

    //Measurement overhead
    data_t ccnt_overhead; 
    ccnt_overhead = get_overhead();
    printf("Reading overhead time is : %f\n", ccnt_overhead);
   
    char buffer1[34]; //100 bytes = 34 + 66
    char buffer2[134];
    char buffer3[234];
    char buffer4[334];
    char buffer5[434];
    char buffer6[534];
    char buffer7[634];
    char buffer8[734];
    char buffer9[834];
    char buffer10[934];
  	
    if (argc < 3) {
	printf("shup up and put the hell portnum and hostname \n");

	exit(1);
    }
	 
    bzero(buffer1, 34);
    bzero(buffer2, 134);
    bzero(buffer3, 234);
    bzero(buffer4, 334);
    bzero(buffer5, 434);
    bzero(buffer6, 534);
    bzero(buffer7, 634);
    bzero(buffer8, 734);
    bzero(buffer9, 834);
    bzero(buffer10, 934);
  	
    strncpy(buffer1, "hello", 5); 
    strncpy(buffer2, "hello", 5);
    strncpy(buffer3, "hello", 5); 
    strncpy(buffer4, "hello", 5);
    strncpy(buffer5, "hello", 5); 
    strncpy(buffer6, "hello", 5); 
    strncpy(buffer7, "hello", 5); 
    strncpy(buffer8, "hello", 5);
    strncpy(buffer9, "hello", 5); 
    strncpy(buffer10, "hello", 5); 

    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0) {

        error("ERROR opening socket");
    }
    
    server = gethostbyname(argv[1]);
    
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
    
        exit(0);
    }
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    option = atoi(argv[3]);

    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
        error("ERROR connecting");
    }

    //test 1: send 100 bytes 
    for(int i = 0 ; i < TRIALS ; ++i) {
        if(option == 1) {
            start = ccnt_read();
            wn = write(sockfd,buffer1,34);
            rn = read(sockfd,buffer1,34);
            end = ccnt_read();
        } else if(option == 2) {
            start = ccnt_read();
            wn = write(sockfd,buffer2,134); 
            rn = read(sockfd,buffer2,134);
            end = ccnt_read();	
        } else if(option == 3) {
            start = ccnt_read();
            wn = write(sockfd,buffer3,234); 
            rn = read(sockfd,buffer3,234);
            end = ccnt_read();	
        }  else if(option == 4) {
            start = ccnt_read();
            wn = write(sockfd,buffer4,334); 
            rn = read(sockfd,buffer4,334);
            end = ccnt_read();	
        } else if(option == 5) {
            start = ccnt_read();
            wn = write(sockfd,buffer5,434); 
	 rn = read(sockfd,buffer5,434);
	 end = ccnt_read();	
        } else if(option == 6) {
            start = ccnt_read();
            wn = write(sockfd,buffer6,534); 
            rn = read(sockfd,buffer6,534);
            end = ccnt_read();	
        } else if(option == 7) {
            start = ccnt_read();
            wn = write(sockfd,buffer7,634); 
            rn = read(sockfd,buffer7,634);
            end = ccnt_read();	
        } else if(option == 8) {
            start = ccnt_read();
            wn = write(sockfd,buffer8,734); 
            rn = read(sockfd,buffer8,734);
            end = ccnt_read();	
        } else if(option == 9) {
            start = ccnt_read();
            wn = write(sockfd,buffer9,834); 
	 rn = read(sockfd,buffer9,834);
	 end = ccnt_read();	
        } else if(option == 10) {
            start = ccnt_read();
            wn = write(sockfd,buffer10,934); 
	 rn = read(sockfd,buffer10,934);
	 end = ccnt_read();	
        } 

        if (wn < 0) {
            error("ERROR writing to socket");
        }

        if (rn < 0) {
            error("ERROR reading from socket");
        }

        double temp = (double)end-start-ccnt_overhead; 
        
        if(max_val < temp) {
	max_val = temp; 
        }
   	
        if(min_val > temp) {
            min_val = temp; 
        }

        total += temp;
        result[i] = temp;
    } 
    
    for(int i = 0 ; i < TRIALS ; ++i) {
        for(int j = i + 1 ; j < TRIALS ; ++j) {
            if(result[j] < result[i]) {
                double temp = result[j];
                result[j] = result[i];
                result[i] = temp;
	} 
        }
	
        std += pow((result[i] - total/TRIALS), 2);
    }
 
    printf("mean: %f \n", total/TRIALS);
    printf("max: %f \n", max_val);
    printf("min: %f \n", min_val);
    printf("median: %f \n", result[TRIALS/2]);
    printf("std: %f \n", sqrt(std/(TRIALS-1)));
        
    return 0;
}
