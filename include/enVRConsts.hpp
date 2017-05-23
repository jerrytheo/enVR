#ifndef _ENVR_CONSTANTS
#define _ENVR_CONSTANTS

namespace enVR {
	const int dim = 500;

	/* typedefs for long types. */
	typedef std::array<GLfloat, 3> points;
	typedef std::set<points> point_set;
	typedef std::map<std::string, point_set> point_map;
	typedef std::map<std::string, cv::Mat> frame_map;
}

#endif
