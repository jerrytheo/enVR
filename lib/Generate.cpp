#include "Generate.hpp"
#include <GL/gl.h>

using namespace enVR;

// Declarations for this file.

static point_set extrapolate_front(cv::Mat fframe, double lthresh,
								   double uthresh);
static point_set extrapolate_left (cv::Mat lframe, double lthresh,
								   double uthresh);
static point_set extrapolate_back (cv::Mat bframe, double lthresh,
								   double uthresh);
static point_set extrapolate_right(cv::Mat rframe, double lthresh,
								   double uthresh);
static point_set extrapolate_top  (cv::Mat tframe, double lthresh,
								   double uthresh);


/*
 * extrapolate_projection - Screens all points not within lthresh and
 * uthresh. Extrapolates the rest of the frame to create a 3D image.
 *
 * Parameters:
 *   cv::Mat frame := The frame to extrapolate.
 *   std::string face := The face to extrapolate for.
 *   double lthresh := The lower end threshold.
 *   double uthresh := The upper end threshold.
 *
 *  Returns:
 *    point_set := A set of points that form the projection for the
 *      corresponding face.
 */
point_set extrapolate_projection(cv::Mat frame, std::string face,
										double lthresh, double uthresh)
{
	point_set pts;
	if      (face == "front") pts = extrapolate_front(frame, lthresh, uthresh);
	else if (face == "left")  pts = extrapolate_left (frame, lthresh, uthresh);
	else if (face == "back")  pts = extrapolate_back (frame, lthresh, uthresh);
	else if (face == "right") pts = extrapolate_right(frame, lthresh, uthresh);
	else if (face == "top")   pts = extrapolate_top  (frame, lthresh, uthresh);
	return pts;
}


/* Extrapolate the front face. */
static point_set extrapolate_front(cv::Mat fframe, double lthresh,
										  double uthresh)
{
	point_set pts;
	for (uint i=0; i < dim; ++i) {
		for (uint j=0; j < dim; ++j) {
			GLfloat pixel = fframe.at<GLfloat>(i, j);
			if (pixel > lthresh && pixel < uthresh) {
				for (uint k=0; k < dim; ++k) {
					points pt;
					pt[0] = j;
					pt[1] = dim - i - 1;
					pt[2] = k;
					pts.insert(pt);
				}
			}
		}
	}
	return pts;
}


/* Extrapolate the left face. */
static point_set extrapolate_left(cv::Mat fframe, double lthresh,
										 double uthresh)
{
	point_set pts;
	for (uint i=0; i < dim; ++i) {
		for (uint j=0; j < dim; ++j) {
			GLfloat pixel = fframe.at<GLfloat>(i, j);
			if (pixel > lthresh && pixel < uthresh) {
				for (uint k=0; k < dim; ++k) {
					points pt;
					pt[0] = k;
					pt[1] = dim - i - 1;
					pt[2] = j;
					pts.insert(pt);
				}
			}
		}
	}
	return pts;
}


/* Extrapolate the back face. */
static point_set extrapolate_back(cv::Mat fframe, double lthresh,
										 double uthresh)
{
	point_set pts;
	for (uint i=0; i < dim; ++i) {
		for (uint j=0; j < dim; ++j) {
			GLfloat pixel = fframe.at<GLfloat>(i, j);
			if (pixel > lthresh && pixel < uthresh) {
				for (uint k=0; k < dim; ++k) {
					points pt;
					pt[0] = dim - j - 1;
					pt[1] = dim - i - 1;
					pt[2] = k;
					pts.insert(pt);
				}
			}
		}
	}
	return pts;
}


/* Extrapolate the right face. */
static point_set extrapolate_right(cv::Mat fframe, double lthresh,
										  double uthresh)
{
	point_set pts;
	for (uint i=0; i < dim; ++i) {
		for (uint j=0; j < dim; ++j) {
			GLfloat pixel = fframe.at<GLfloat>(i, j);
			if (pixel > lthresh && pixel < uthresh) {
				for (uint k=0; k < dim; ++k) {
					points pt;
					pt[0] = k;
					pt[1] = dim - i - 1;
					pt[2] = dim - j - 1;
					pts.insert(pt);
				}
			}
		}
	}
	return pts;
}


/* Extrapolate the top face. */
static point_set extrapolate_top(cv::Mat fframe, double lthresh,
										double uthresh)
{
	point_set pts;
	for (uint i=0; i < dim; ++i) {
		for (uint j=0; j < dim; ++j) {
			GLfloat pixel = fframe.at<GLfloat>(i, j);
			if (pixel > lthresh && pixel < uthresh) {
				for (uint k=0; k < dim; ++k) {
					points pt;
					pt[0] = j;
					pt[1] = k;
					pt[2] = i;
					pts.insert(pt);
				}
			}
		}
	}
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
point_set construct_3d_image(point_map pmap)
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
