#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h> 

// video libraries
#include <opencv2/videoio.hpp>
#include <opencv2/opencv.hpp>

// communication libraries
#include <unistd.h> 
#include <sys/socket.h> 
#include <sys/types.h>
#include <netinet/in.h> 
#include <arpa/inet.h>

// video related functions
cv::VideoCapture video_capture_init();
int jpg_encode(cv::Mat frame, char* buffer);

// communication related macros
#define PORT 4000
#define CLIENT_PORT 3000 //depends on base station server app
#define CLIENT_ADDR "127.0.0.1"  //depends on base station server app

// communication related functions
int socket_gen(struct sockaddr_in* servaddr_ref);
void fill_client_info(struct sockaddr_in* cliaddr_ref);
