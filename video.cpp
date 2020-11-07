#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/videoio.hpp>
#include <string>
#include <vector>

#define uchar unsigned char

int main(int argc, char** argv) {

	cv::VideoCapture cap(0);
	
	if(!cap.isOpened()) {
  		std::cout << "error opening camera" << std::endl;
		return -1;
	}

	std::cout << "camera successfully opened" << std::endl;

	while (true) {
		cv::Mat frame;
		cap >> frame;

		if (frame.empty()) {
			break;
		}
		cv::imshow("Frame", frame);
		//out.write(frame);
		/*std::vector<uchar> buf_vector;
		cv::imencode(".jpg", frame, buf, std::vector<int>());
		char* buffer = &buf_vector[0];
		int buffer_size = buf_vector.size();
*/
		char c = (char) cv::waitKey(25);

		if (c == 27) {
			break;
		}
	}
	cap.release();
	cv::destroyAllWindows();

	return 0;
}
