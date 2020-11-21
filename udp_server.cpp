#include "udp_server.h"

// generates the server socket
void socket_gen(int* sock_fd_ptr, struct sockaddr_in * servaddr_ref,
								struct sockaddr_in * cliaddr_ref) 
{ 
	int sock_fd;
	struct sockaddr_in servaddr, cliaddr;	
	
	// Creating socket file descriptor 
	if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	}

	memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr));

	servaddr.sin_family = AF_INET;// IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons( PORT ); 
	
	// binds socket to port
	if (bind(sock_fd, (struct sockaddr *)&servaddr, 
								sizeof(servaddr))<0) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	}

	//updates values at pointers stored in scope of stream
	*sock_fd_ptr = sock_fd;
	*servaddr_ref = servaddr;
	*cliaddr_ref = cliaddr;
}

// listens and accepts connection from base station
// returns socket id of client socket
int listen_for_connection(int sock_fd, struct sockaddr_in * servaddr_ref,
                                 int servaddr_len){
    // marks socket as accepting connection
	if (listen(sock_fd, 3) < 0) 
 	{ 
	    perror("listen"); 
 		exit(EXIT_FAILURE); 
	}

	int new_socket;
	//accepts connection from base station
	if ((new_socket = accept(sock_fd, (struct sockaddr *)servaddr_ref, 
                     (socklen_t*)&servaddr_len))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    }
	return new_socket;
}

//send header for mjpeg streaming
void send_mjpeg_format(int sock_fd) {
	std::string header;
    header += "HTTP/1.0 200 OK\r\n";
	header += "browser-sync:^2.26.13";
    header += "Cache-Control: no-cache\r\n";
    header += "Pragma: no-cache\r\n";
    header += "Connection: close\r\n";
    header += "Content-Type: multipart/x-mixed-replace; boundary=mjpegstream\r\n\r\n";
    const int header_size = header.size();
    char* header_data = (char*)header.data();

	send(sock_fd, header_data, header_size, 0);
}
