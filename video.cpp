#include "video.h"

//starts video camera capture process
cv::VideoCapture video_capture_init() {

	cv::VideoCapture cap(0);
	
	if(!cap.isOpened()) {
  		std::cout << "error opening camera" << std::endl;
		exit(-1);
	}

	std::cout << "camera successfully opened" << std::endl;
	
	return cap;
}

//closes camera access
void video_capture_close(cv::VideoCapture cap) {
	cap.release();                                                                                   
	cv::destroyAllWindows();
}

// encodes an opencv mat as a jpeg, stored in buffer
// returns size of the buffer
int jpg_encode(cv::Mat frame, char* buffer) {
	std::vector<uchar> buf_vector;
	//encodes the frame into buf_vector
    cv::imencode(".jpg", frame, buf_vector, std::vector<int>());
	//converts the encoded vector into a buffer array of bytes
    buffer = reinterpret_cast<char*> (buf_vector.data());
    printf("buf_vector.size(): %d\n", (int)buf_vector.size());
	return buf_vector.size();
}
