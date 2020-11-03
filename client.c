#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#define PORT 18520

int main() {
	struct sockaddr_in serv_addr;
	int sock = 0;
	const char *addr = "127.0.0.1";
	char msg[1024];
	
	memset(msg, '0',sizeof(msg));

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Socket creation failed!\n");
		return -1;
	} else {
		printf("Socket created\n");
	}
	
	memset(&serv_addr, '0', sizeof(serv_addr)); 

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
		printf("Check your address dude\n");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		perror("Connection failed: ");
		return -1;
	} else {
		printf("Connected to server\n");
	}
	
	int pro = 0;
	while(1) {
		printf("Message >>> ");
		bzero(msg, 256);
		fgets(msg, 255, stdin);
		printf("\nSending message: %s", msg);
		if ((pro = send(sock, msg, strlen(msg), 0)) < 0) {
			perror("Failed/sending/: ");
			return 0;
		}
		
		bzero(msg, 256);
		if ((pro = recv(sock, msg, 255, 0)) < 0) {
			perror("Failed/receiving/: ");
			return 0;
		} else {
			printf("Message received: %s", msg);
		}
	}
	close(sock);
	return 0;
}


/*
struct sockaddr_in serv;
int fd;
int conn;
char message[100] = "";
fd = socket(AF_INET, SOCK_STREAM, 0);
serv.sin_family = AF_INET;
serv.sin_port = htons(8096);
inet_pton(AF_INET, "127.0.0.1", &serv.sin_addr);
connect(fd, (struct sockaddr *)&serv, sizeof(serv));
while(1) {
		printf("Text oruulna uu: ");
		fgets(message, 100, stdin);
		send(fd, message, strlen(message), 0);
	strcpy(message,"");
	recv(fd, message, 100, 0);
	printf("irsen text: %s", message);
}
*/
