#ifndef _ENVR_CAPTURE
#define _ENVR_CAPTURE

#include "enVRConsts.hpp"

namespace enVR {
	frame_map capture_images();
	void save_frames(frame_map);
	frame_map read_frames();
}

#endif
