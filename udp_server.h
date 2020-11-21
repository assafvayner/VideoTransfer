#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string>
#include <cstring>
#define PORT 8080 

void socket_gen(int* sock_fd_ptr, struct sockaddr_in * servaddr_ref,
                                 struct sockaddr_in * cliaddr_ref);
int listen_for_connection(int sock_fd, struct sockaddr_in * servaddr_ref,
                                 int servaddr_len);
void send_mjpeg_format(int sock_fd);								
