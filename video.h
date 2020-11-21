#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/videoio.hpp>
#include <string>
#include <vector>

#define uchar unsigned char

cv::VideoCapture video_capture_init();
void video_capture_close(cv::VideoCapture cap);
int jpg_encode(cv::Mat frame, char* buffer);
