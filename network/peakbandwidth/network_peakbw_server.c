#include "net_test.h"

void error(const char *msg) {
	perror(msg);

	exit(0);
}

void respond_to_client(int sock) {
	int n;

	printf("Responding...");

	for(int i = 0; i < SEND_COUNT; i++) {
		printf("\r");
		char buffer[WINDOWSIZE];

		bzero(buffer,WINDOWSIZE);
	
		n = read(sock,buffer,WINDOWSIZE-1);
		if (n < 0) {
			error("ERROR reading from socket");
		}

		n = write(sock,"I got your message",18);
		
		if (n < 0) {
			error("ERROR writing to socket");
		}

		printf("Message received. %d", i);
	}

	printf("\n");
}

void peakbandwidth_server() {
	int i=0, sockfd, newsockfd, portno, pid;
	struct sockaddr_in serv_addr, cli_addr;
	socklen_t clilen;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0) {
		error("ERROR opening socket");
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = SOCKETNO;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(6667);
	
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		error("ERROR on binding");
	} 

	listen(sockfd,5);
	clilen = sizeof(cli_addr);

	printf("Starting server.\n");
	
	while(1) {
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		if (newsockfd < 0) {
			error("ERROR on accept");
		}

		printf("======================================================================\n");
		printf("Connection started.\n");
		i++; 
		printf("Probably in trial %d\n", i);
		
		pid = fork();
		
		if (pid < 0) {
			error("ERROR on fork");
		}

		if (pid == 0) {
			close(sockfd);
			
			respond_to_client(newsockfd);
			
			exit(0);
		} else {
			close(newsockfd);
		}
	}

	close(sockfd);
	
	return; 
}

int main(int argc, char *argv[]) {
	peakbandwidth_server();

	return 0;
}