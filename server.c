#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#define PORT 18520

int main() {
	struct sockaddr_in serv;
	int server;
	int opt = 1;
	char message[1026];
	char rsms[1026];
	
	memset(message, '0',sizeof(message));
	memset(&serv, '0', sizeof(serv)); 


	if ((server = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		perror("Socket creation failed!");
		return -1;
	}

	if (setsockopt(server, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		perror("Setsocketoption");
		return -1;
	}

	serv.sin_family = AF_INET;
	serv.sin_port = htons(PORT);
	serv.sin_addr.s_addr = INADDR_ANY;

	if (bind(server, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
		perror("Bind process failed");
		return -1;
	}

	if (listen(server, 3) < 0) {
		perror("not listening!");
		return -1;
	}
	puts("WAITING FOR CONNECTION......");

	int conn = 0;
	while(conn = accept(server, (struct sockaddr *)NULL, NULL)) {
	    //printf("Device connected to server --- %s::%d\n", inet_ntoa(serv.sin_addr), ntohs(serv.sin_port));
	    int pid, n = 0;
	    if((pid = fork()) == 0) {
		close(server);
		
		bzero(message, 256);
		bzero(rsms, 256);
		
		while( (n = recv(conn, message, 255, 0)) > 0 ) {
			printf("\nRecieved msg: %s", message);
			int se = 0;
			printf("\nMessage >>> ");
			fgets(rsms, 255, stdin);
			if ((se = send(conn, rsms, strlen(rsms), 0)) < 0) {
				perror("\nSending failed: ");
				return 0;
			} else {
				printf("\nMessage sent");
			}
		}
		close(conn);
	    }
	}
	return 0;
}
