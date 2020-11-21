#include "video.h"
#include "udp_server.h"

int main(int argc, char** argv) {
	//start camera access
	cv::VideoCapture cap = video_capture_init();
	printf("camera successfully opened\n");

	//create server socket
	int sock_fd;
    struct sockaddr_in servaddr, cliaddr;
	socket_gen(&sock_fd, &servaddr, &cliaddr);
	printf("socket generated successfully\n");

	//connect to base station
	int client_sock = listen_for_connection(sock_fd, &servaddr, sizeof(servaddr));
	printf("connected to base station\n");

	//send mjpeg header
	send_mjpeg_format(sock_fd);
	printf("send mjpeg header\n");
	
	//initialize large space in memory for buffer
	char* buffer = (char*)malloc(1 << 22);
	int buffer_size;

	while (true) {
		// take camera input and use as cv::Mat
		cv::Mat frame;
		cap >> frame;

		//display feed
		//cv::imshow("Frame", frame);
		
		//encode current camera feed as jpg and send it
		buffer_size = jpg_encode(frame, buffer);
		send(sock_fd, buffer, buffer_size, 0);

		// hit esc to exit loop
		char c = (char) cv::waitKey(25);
		if (c == 27) {
			break;
        }

	}

	// deallocate buffer memory
	free(buffer);
	// close server socket
	close(sock_fd);
	printf("closed socket successfully\n");
	// close camera input
	video_capture_close(cap);
	printf("closed camera successfully\n");
	printf("finite\n");
	return 0;

}
