#ifndef _ENVR_POINTGEN
#define _ENVR_POINTGEN

#include "enVRConsts.hpp"

namespace enVR {
	point_set extrapolate_projection(cv::Mat, std::string,
									 uchar, uchar, uchar);
	point_set construct_3d_image(point_map);
}

#endif
