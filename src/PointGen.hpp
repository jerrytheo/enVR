#ifndef _ENVR_POINTGEN
#define _ENVR_POINTGEN

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>

#include <GL/gl.h>
#include <opencv2/opencv.hpp>

#include "Capture.hpp"

typedef std::vector<GLfloat> points;

std::set<points> extrapolate_front_projection(cv::Mat fframe)
{
	std::set<points> gen_pts;
	cv::imwrite("front.jpg", fframe);
	for (int i=0; i < DIM; ++i) {
		for (int j=0; j < DIM; ++j) {
			if (fframe.at<GLfloat>(i, j) < 1e+100) {
				points pt;
				pt.push_back(j);
				pt.push_back(DIM - i - 1);
				pt.push_back(1);
				gen_pts.insert(pt);
			}
		}
	}
	return gen_pts;
}

std::set<points> extrapolate_left_projection(cv::Mat lframe)
{
	std::set<points> gen_pts;
	cv::imwrite("left.jpg", lframe);
	for (int i=0; i < DIM; ++i) {
		for (int j=0; j < DIM; ++j) {
			if (lframe.at<GLfloat>(i, j) < 1e+100) {
				points pt;
				pt.push_back(j);
				pt.push_back(DIM - i - 1);
				pt.push_back(1);
				gen_pts.insert(pt);
			}
		}
	}
	return gen_pts;
}

std::set<points> extrapolate_back_projection(cv::Mat bframe)
{
	std::set<points> gen_pts;
	cv::imwrite("back.jpg", bframe);
	for (int i=0; i < DIM; ++i) {
		for (int j=0; j < DIM; ++j) {
			if (bframe.at<GLfloat>(i, j) < 1e+100) {
				points pt;
				pt.push_back(j);
				pt.push_back(DIM - i - 1);
				pt.push_back(1);
				gen_pts.insert(pt);
			}
		}
	}
	return gen_pts;
}

std::set<points> extrapolate_right_projection(cv::Mat rframe)
{
	std::set<points> gen_pts;
	cv::imwrite("right.jpg", rframe);
	for (int i=0; i < DIM; ++i) {
		for (int j=0; j < DIM; ++j) {
			if (rframe.at<GLfloat>(i, j) < 1e+100) {
				points pt;
				pt.push_back(j);
				pt.push_back(DIM - i - 1);
				pt.push_back(1);
				gen_pts.insert(pt);
			}
		}
	}
	return gen_pts;
}

std::set<points> extrapolate_top_projection(cv::Mat tframe)
{
	std::set<points> gen_pts;
	cv::imwrite("top.jpg", tframe);
	for (int i=0; i < DIM; ++i) {
		for (int j=0; j < DIM; ++j) {
			if (tframe.at<GLfloat>(i, j) < 1e+100) {
				points pt;
				pt.push_back(j);
				pt.push_back(DIM - i - 1);
				pt.push_back(1);
				gen_pts.insert(pt);
			}
		}
	}
	return gen_pts;
}

std::vector<GLfloat*> generate_points()
{
	using std::string;
	auto frames = capture_images();

	auto front_points = extrapolate_front_projection(frames["front"]);
	auto left_points  = extrapolate_left_projection(frames["left"]);
	auto back_points  = extrapolate_back_projection(frames["back"]);
	auto right_points = extrapolate_right_projection(frames["right"]);
	auto top_points   = extrapolate_top_projection(frames["top"]);
/*
	std::set<points> inter;
	std::set_intersection(front_points.begin(),
						  front_points.end(),
						  left_points.begin(),
						  left_points.end(),
						  std::back_inserter(inter));
	std::set_intersection(inter.begin(),
						  inter.end(),
						  back_points.begin(),
						  back_points.end(),
						  std::back_inserter(inter));
	std::set_intersection(inter.begin(),
						  inter.end(),
						  right_points.begin(),
						  right_points.end(),
						  std::back_inserter(inter));

	std::set_intersection(inter.begin(),
						  inter.end(),
						  top_points.begin(),
						  top_points.end(),
						  std::back_inserter(inter));
*/
	std::vector<GLfloat*> final_points;
//	for (std::set<points>::iterator it = inter.begin(); it != inter.end(); ++it) {
	for (std::set<points>::iterator it = front_points.begin(); it != front_points.end(); ++it) {
		GLfloat* pt = new GLfloat[3];
		pt[0] = (*it)[0];
		pt[1] = (*it)[1];
		pt[2] = (*it)[2];
		final_points.push_back(pt);
	}
	return final_points;
}

#endif