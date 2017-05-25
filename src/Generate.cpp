/*
 * Generate.cpp - Functions that construct the 3D image from the 2D
 * projections stored as OpenCV matrices.
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

#include "Generate.hpp"
#include <GL/gl.h>

using namespace enVR;

// Declarations for this file.

static point_set extrapolate_front(const cv::Mat&, const uchar*,
								   const uchar*, const uchar*);
static point_set extrapolate_left (const cv::Mat&, const uchar*,
								   const uchar*, const uchar*);
static point_set extrapolate_back (const cv::Mat&, const uchar*,
								   const uchar*, const uchar*);
static point_set extrapolate_right(const cv::Mat&, const uchar*,
								   const uchar*, const uchar*);
static point_set extrapolate_top  (const cv::Mat&, const uchar*,
								   const uchar*, const uchar*);


/*
 * extrapolate_projection - Screens all points not within lthresh and
 * uthresh. Extrapolates the rest of the frame to create a 3D image.
 *
 * Parameters:
 *   const cv::Mat& frame := The frame to extrapolate.
 *   std::string face := The face to extrapolate for.
 *   const uchar* rthresh := The red color threshold.
 *   const uchar* gthresh := The green color threshold.
 *   const uchar* bthresh := The blue color threshold.
 *
 *  Returns:
 *    point_set := A set of points that form the projection for the
 *      corresponding face.
 */
point_set enVR::extrapolate_projection(const cv::Mat& frame,
									   std::string face,
									   const uchar* rthresh,
									   const uchar* gthresh,
									   const uchar* bthresh)
{
	point_set pts;
	if      (face == "front") pts = extrapolate_front(frame, rthresh, gthresh, bthresh);
	else if (face == "left")  pts = extrapolate_left (frame, rthresh, gthresh, bthresh);
	else if (face == "back")  pts = extrapolate_back (frame, rthresh, gthresh, bthresh);
	else if (face == "right") pts = extrapolate_right(frame, rthresh, gthresh, bthresh);
	else if (face == "top")   pts = extrapolate_top  (frame, rthresh, gthresh, bthresh);
	return pts;
}


/*
 *  construct_3d_image - Returns a set of vertices that when drawn
 *  using OpenGL form a 3D representation of the original projections.
 *
 *  Parameters:
 *    point_map pmap := A map that associates each face with a set of
 *      points.
 *
 *  Returns:
 *    point_set := A set of points to be drawn in OpenGL.    
 */
point_set enVR::construct_3d_image(point_map& pmap)
{
	point_set inter, inter2;

	// Intersection of front and left.
	std::set_intersection(pmap["front"].begin(), pmap["front"].end(),
						  pmap["left"].begin(), pmap["left"].end(),
						  std::inserter(inter, inter.end()));

	// Intersection of inter and back.
	std::set_intersection(inter.begin(), inter.end(),
						  pmap["back"].begin(), pmap["back"].end(),
						  std::inserter(inter2, inter2.end()));
	
	inter.clear();
	// Intersection of inter and right.
	std::set_intersection(inter2.begin(), inter2.end(),
						  pmap["right"].begin(), pmap["right"].end(),
						  std::inserter(inter, inter.end()));
	inter2.clear();
	// Intersection of inter and top.
	std::set_intersection(inter.begin(), inter.end(),
						  pmap["top"].begin(), pmap["top"].end(),
						  std::inserter(inter2, inter2.end()));

	return inter2;
}


/* Extrapolate the front face. */
static point_set extrapolate_front(const cv::Mat& frame, const uchar* rthresh,
								   const uchar* gthresh, const uchar* bthresh)
{
	point_set pts;
	for (uint i=0; i < dim; ++i) {
		const uchar* p = frame.ptr(i);
		for (uint j=0; j < dim; ++j) {
			uchar green = *p++;
			uchar blue  = *p++;
			uchar red   = *p++;
			if (red > rthresh[0] && red < rthresh[1])
				if (green > gthresh[0] && green < gthresh[1])
					if (blue > bthresh[0] && blue < bthresh[1])
						for (uint k=0; k < dim; ++k) {
							points pt;
							pt[0] = j;
							pt[1] = dim - i - 1;
							pt[2] = k;
							pts.insert(pt);
						}
		}
	}
	return pts;
}


/* Extrapolate the left face. */
static point_set extrapolate_left(const cv::Mat& frame, const uchar* rthresh,
								  const uchar* gthresh, const uchar* bthresh)
{
	point_set pts;
	for (uint i=0; i < dim; ++i) {
		const uchar* p = frame.ptr(i);
		for (uint j=0; j < dim; ++j) {
			uchar green = *p++;
			uchar blue  = *p++;
			uchar red   = *p++;
			if (red > rthresh[0] && red < rthresh[1])
				if (green > gthresh[0] && green < gthresh[1])
					if (blue > bthresh[0] && blue < bthresh[1])
						for (uint k=0; k < dim; ++k) {
							points pt;
							pt[0] = k;
							pt[1] = dim - i - 1;
							pt[2] = j;
							pts.insert(pt);
						}
		}
	}
	return pts;
}


/* Extrapolate the back face. */
static point_set extrapolate_back(const cv::Mat& frame, const uchar* rthresh,
								  const uchar* gthresh, const uchar* bthresh)
{
	point_set pts;
	for (uint i=0; i < dim; ++i) {
		const uchar* p = frame.ptr(i);
		for (uint j=0; j < dim; ++j) {
			uchar green = *p++;
			uchar blue  = *p++;
			uchar red   = *p++;
			if (red > rthresh[0] && red < rthresh[1])
				if (green > gthresh[0] && green < gthresh[1])
					if (blue > bthresh[0] && blue < bthresh[1])
						for (uint k=0; k < dim; ++k) {
							points pt;
							pt[0] = dim - j - 1;
							pt[1] = dim - i - 1;
							pt[2] = k;
							pts.insert(pt);
						}
		}
	}
	return pts;
}


/* Extrapolate the right face. */
static point_set extrapolate_right(const cv::Mat& frame, const uchar* rthresh,
								   const uchar* gthresh, const uchar* bthresh)
{
	point_set pts;
	for (uint i=0; i < dim; ++i) {
		const uchar* p = frame.ptr(i);
		for (uint j=0; j < dim; ++j) {
			uchar green = *p++;
			uchar blue  = *p++;
			uchar red   = *p++;
			if (red > rthresh[0] && red < rthresh[1])
				if (green > gthresh[0] && green < gthresh[1])
					if (blue > bthresh[0] && blue < bthresh[1])
						for (uint k=0; k < dim; ++k) {
							points pt;
							pt[0] = k;
							pt[1] = dim - i - 1;
							pt[2] = dim - j - 1;
							pts.insert(pt);
						}
		}
	}
	return pts;
}


/* Extrapolate the top face. */
static point_set extrapolate_top(const cv::Mat& frame, const uchar* rthresh,
								 const uchar* gthresh, const uchar* bthresh)
{
	point_set pts;
	for (uint i=0; i < dim; ++i) {
		const uchar* p = frame.ptr(i);
		for (uint j=0; j < dim; ++j) {
			uchar green = *p++;
			uchar blue  = *p++;
			uchar red   = *p++;
			if (red > rthresh[0] && red < rthresh[1])
				if (green > gthresh[0] && green < gthresh[1])
					if (blue > bthresh[0] && blue < bthresh[1])
						for (uint k=0; k < dim; ++k) {
							points pt;
							pt[0] = j;
							pt[1] = k;
							pt[2] = i;
							pts.insert(pt);
						}
		}
	}
	return pts;
}
