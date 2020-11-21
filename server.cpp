#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8080 

// refills buffer with 0's
void resetBuffer(char* buffer, int buffer_len) {
	for (int i = 0; i < buffer_len; i++) {
		buffer[i] = 0;
	}
}


int main(int argc, char const *argv[]) 
{ 
	int server_fd, new_socket, valread; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address);
	int buffer_len = 1024;
	char buffer[buffer_len]; 
	
	// Creating socket file descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	// Forcefully attaching socket to the port 8080 
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
												&opt, sizeof(opt))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	
	// Forcefully attaching socket to the port 8080 
	if (bind(server_fd, (struct sockaddr *)&address, 
								sizeof(address))<0) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	}

	// marks socket as accepting connection	
	if (listen(server_fd, 3) < 0) 
	{ 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	}
	//accept connection from "client"
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
					(socklen_t*)&addrlen))<0) 
	{ 
		perror("accept"); 
		exit(EXIT_FAILURE); 
	} 
	
	while (true) {
		//reset buffer to be all 0's
		resetBuffer(buffer, buffer_len);
		//read value sent from "client", stored in buffer
		valread = read( new_socket , buffer, buffer_len);
		//exit loop if recieved "close" and close socket
		if (!strcmp(buffer, "close")) {
			break;
		}
		//only print if buffer contains information
		if (*buffer != 0) {
			printf("%s\n", buffer);
		}
	}
	
	close(server_fd);
	printf("closed server\n");
	return 0; 
} 
