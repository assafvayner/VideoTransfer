#include "stream.h"


/* intended to stream frames from robot camera to base station using UDP
 * to avoid back and forth communication as there is high potential for
 * communication issues between robot and base station for a large ammount
 * of data on the field. currently streams a jpeg representation of camera
 * feed to client at address and port at CLIENT_ADDR and CLIENT_PORT global vars in
 * udp_server.h, will need to be changed to fit the ip address of the base station
 * and port that the server on the base station will be listening for video
 * stream.
 */
int main(int argc, char** argv) {
	//start camera access
	cv::VideoCapture cap = video_capture_init();
	printf("camera successfully opened\n");

	//create server socket
	int sock_fd;
  struct sockaddr_in servaddr, cliaddr;
	sock_fd = socket_gen(&servaddr);
	printf("video stream socket generated successfully\n");
	fill_client_info(&cliaddr);
	
	//initialize large space in memory for buffer
	char* buffer = (char*)malloc(1 << 21);
	int buffer_size;

	while (true) {
		// take camera input and use as cv::Mat
		cv::Mat frame;
		cap >> frame;

		//display feed
		//cv::imshow("Frame", frame);
		
		//encode current camera feed as jpg and send it
		buffer_size = jpg_encode(frame, buffer);
		sendto(sock_fd, buffer, buffer_size, 0, (sockaddr*)(&cliaddr), sizeof(sockaddr));

		// hit esc to exit loop
		/*char c = (char) cv::waitKey(25);
		if (c == 27) {
			break;
        }
    */

	}

	// deallocate buffer memory
	free(buffer);
	// close server socket
	close(sock_fd);
	printf("closed socket successfully\n");
	// close camera input
	cap.release();                                                                                   
	printf("closed camera successfully\n");
	printf("finite\n");
	return 0;

}

//starts video camera capture process
cv::VideoCapture video_capture_init() {
	cv::VideoCapture cap(0);
	
	if(!cap.isOpened()) {
 		std::cout << "error opening camera" << std::endl;
		exit(-1);
	}

	return cap;
}

// encodes an opencv mat as a jpeg, stored in buffer
// returns size of the buffer
int jpg_encode(cv::Mat frame, char* buffer) {
	std::vector<uchar> buf_vector;
	//encodes the frame into buf_vector
  cv::imencode(".jpg", frame, buf_vector, std::vector<int>());
	//converts the encoded vector into a buffer array of bytes
  buffer = reinterpret_cast<char*> (buf_vector.data());
	return buf_vector.size();
}

// generates the server socket
int socket_gen(struct sockaddr_in * servaddr_ref) { 
	int sock_fd;
	struct sockaddr_in servaddr;
	
	// Creating socket file descriptor 
	if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) == 0) { 
		std::cout << "Failed to create video stream socket" << std::endl;
		exit(0);
	}

	memset(&servaddr, 0, sizeof(servaddr)); 

	servaddr.sin_family = AF_INET;// IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons( PORT ); 
	
	// binds socket to port
	if (bind(sock_fd, (struct sockaddr *)&servaddr, sizeof(servaddr))<0) { 
		std::cout << "Failed to bind video stream socket to port: " << PORT << std::endl;
		exit(0); 
	}

	//updates values at pointers stored in scope of stream
	*servaddr_ref = servaddr;
  
	return sock_fd;
}

void fill_client_info(struct sockaddr_in* cliaddr_ref) {
	sockaddr_in cliaddr;

	memset(&cliaddr, 0, sizeof(cliaddr));
	
	cliaddr.sin_family = AF_INET;
	cliaddr.sin_addr.s_addr = inet_addr(CLIENT_ADDR);
	cliaddr.sin_port = htons(CLIENT_PORT);

  *cliaddr_ref = cliaddr;
}

