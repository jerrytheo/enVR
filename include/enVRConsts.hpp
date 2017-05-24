/*
 * enVRConsts.hpp - Declares constants and convenient typdefs.
 * 
 * Copyright (C) 2017  Abhijit J. Theophilus, Abhishek S. V.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * For the complete license, see LICENSE.md.
 *
 */


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
