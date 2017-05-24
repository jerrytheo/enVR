#ifndef _ENVR_CONSTANTS
#define _ENVR_CONSTANTS

#include <vector>
#include <array>
#include <set>
#include <map>
#include <string>
#include <GL/freeglut.h>
#include <opencv2/opencv.hpp>


namespace enVR {
	const int dim = 200;
	const std::vector<std::string> faces {"front", "left", "back", "right",
										  "top"};

	/* typedefs for long types. */
	typedef std::array<GLfloat, 3> points;
	typedef std::set<points> point_set;
	typedef std::map<std::string, point_set> point_map;
	typedef std::map<std::string, cv::Mat> frame_map;
}

#endif
