#include <iostream>
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 8080 

//gets a short message from stdin to send to the server to print
char const * getMessage() {	
    std::string message;
    std::getline(std::cin, message);
	return message.c_str();
}

int main(int argc, char *argv[]) 
{ 
    int sock = 0, valread;
    struct sockaddr_in serv_addr; 
	char const * message;
	//create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    }
   //create connection to "server"
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    }
	printf("connected to server\n");
	
	while (true) {
   		message = getMessage();
   		send(sock , message, strlen(message), 0); 
		// if message is "close", exit loop to close the socket after sending
		// "close" to server
		if (!strcmp(message, "close")){
			break;
		}
	}
	close(sock);
    return 0; 
}
