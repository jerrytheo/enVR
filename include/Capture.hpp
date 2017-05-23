#ifndef _ENVR_CAPTURE
#define _ENVR_CAPTURE

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "enVRConsts.hpp"

namespace enVR {
	std::map<std::string, cv::Mat> capture_images();
	void save_frames(std::vector<cv::Mat>);
}

#endif
