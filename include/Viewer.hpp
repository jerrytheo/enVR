#ifndef _ENVR_VIEWER
#define _ENVR_VIEWER

#include <GL/glut.h>
#include "enVRConsts.hpp"

namespace enVR {
	void init_viewer(int* argc, char** argv);
	void view_3d_image(point_set pset);
}

#endif
