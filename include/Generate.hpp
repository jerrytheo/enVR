#ifndef _ENVR_POINTGEN
#define _ENVR_POINTGEN

#include <set>
#include <array>
#include <string>
#include <map>
#include <vector>

#include <GL/gl.h>
#include <opencv2/opencv.hpp>

#include "enVRConsts.hpp"

namespace enVR {
	point_set extrapolate_projection(cv::Mat frame, std::string face,
									double lthresh, double uthresh);
	point_set construct_3d_image(point_map pmap);
}

#endif
