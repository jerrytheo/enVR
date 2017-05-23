#include "Generate.hpp"

using namespace enVR;

// Declarations for this file.

static point_set extrapolate_front(cv::Mat fframe);
static point_set extrapolate_left (cv::Mat lframe);
static point_set extrapolate_back (cv::Mat bframe);
static point_set extrapolate_right(cv::Mat rframe);
static point_set extrapolate_top  (cv::Mat tframe);


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
	for (int i=0; i < DIM; ++i) {
		for (int j=0; j < DIM; ++j) {
			GLfloat pixel = fframe.at<GLfloat>(i, j);
			if (pixel > lthresh && pixel < uthresh) {
				for (int k=0; k < DIM; ++k) {
					points pt;
					pt[0] = j;
					pt[1] = DIM - i - 1;
					pt[2] = k;
					gen_pts.insert(pt);
				}
			}
		}
	}
	return gen_pts;
}


/* Extrapolate the left face. */
static point_set extrapolate_left(cv::Mat fframe, double lthresh,
										 double uthresh)
{
	point_set pts;
	for (int i=0; i < DIM; ++i) {
		for (int j=0; j < DIM; ++j) {
			GLfloat pixel = fframe.at<GLfloat>(i, j);
			if (pixel > lthresh && pixel < uthresh) {
				for (int k=0; k < DIM; ++k) {
					points pt;
					pt[0] = k;
					pt[1] = DIM - i - 1;
					pt[2] = j;
					gen_pts.insert(pt);
				}
			}
		}
	}
	return gen_pts;
}


/* Extrapolate the back face. */
static point_set extrapolate_back(cv::Mat fframe, double lthresh,
										 double uthresh)
{
	point_set pts;
	for (int i=0; i < DIM; ++i) {
		for (int j=0; j < DIM; ++j) {
			GLfloat pixel = fframe.at<GLfloat>(i, j);
			if (pixel > lthresh && pixel < uthresh) {
				for (int k=0; k < DIM; ++k) {
					points pt;
					pt[0] = DIM - j - 1;
					pt[1] = DIM - i - 1;
					pt[2] = k;
					gen_pts.insert(pt);
				}
			}
		}
	}
	return gen_pts;
}


/* Extrapolate the right face. */
static point_set extrapolate_right(cv::Mat fframe, double lthresh,
										  double uthresh)
{
	point_set pts;
	for (int i=0; i < DIM; ++i) {
		for (int j=0; j < DIM; ++j) {
			GLfloat pixel = fframe.at<GLfloat>(i, j);
			if (pixel > lthresh && pixel < uthresh) {
				for (int k=0; k < DIM; ++k) {
					points pt;
					pt[0] = k;
					pt[1] = DIM - i - 1;
					pt[2] = DIM - j - 1;
					gen_pts.insert(pt);
				}
			}
		}
	}
	return gen_pts;
}


/* Extrapolate the top face. */
static point_set extrapolate_top(cv::Mat fframe, double lthresh,
										double uthresh)
{
	point_set pts;
	for (int i=0; i < DIM; ++i) {
		for (int j=0; j < DIM; ++j) {
			GLfloat pixel = fframe.at<GLfloat>(i, j);
			if (pixel > lthresh && pixel < uthresh) {
				for (int k=0; k < DIM; ++k) {
					points pt;
					pt[0] = j;
					pt[1] = k;
					pt[2] = i;
					gen_pts.insert(pt);
				}
			}
		}
	}
	return gen_pts;
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
	point_set inter;

	// Intersection of front and left.
	std::set_intersection(pmap["front"].begin(), pmap["front"].end(),
						  pmap["left"].begin(), pmap["left"].end(),
						  std::back_inserter(inter));

	// Intersection of inter and back.
	std::set_intersection(inter.begin(), inter.end(),
						  pmap["back"].begin(), pmap["back"].end(),
						  std::back_inserter(inter));

	// Intersection of inter and right.
	std::set_intersection(inter.begin(),
						  inter.end(),
						  pmap["right"].begin(),
						  pmap["right"].end(),
						  std::back_inserter(inter));

	std::set_intersection(inter.begin(), inter.end(),
						  pmap["top"].begin(), pmap["top"].end(),
						  std::back_inserter(inter));

	return inter;
}
