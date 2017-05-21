#ifndef _ENVR_CAPTURE
#define _ENVR_CAPTURE

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <map>
#include <vector>

const int DIM = 500;

std::map<std::string, cv::Mat> capture_images();
void save_frames(std::vector<cv::Mat>);

#endif
