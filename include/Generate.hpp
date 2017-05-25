/*
 * Generate.hpp - Header file for Generate.cpp.
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

#ifndef _ENVR_POINTGEN
#define _ENVR_POINTGEN

#include "enVRConsts.hpp"

namespace enVR {
	point_set extrapolate_projection(const cv::Mat&,
									 std::string,
									 const uchar*,
									 const uchar*,
									 const uchar*);
	point_set construct_3d_image(point_map&);
}

#endif
