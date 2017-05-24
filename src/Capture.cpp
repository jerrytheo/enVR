/*
 * Capture.cpp - A set of functions to interface either the cameras or
 * filesystem.
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

#include "Capture.hpp"
#include <iostream>

using namespace enVR;

/*
 * capture_images - Captures images sequentially from each of the
 * cameras attached and returns an std::map that associates each image
 * with the camera attached.
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   frame_map := Associates the cube face with
 *     the captured image.
 */

frame_map enVR::capture_images()
{
	using std::string;
	frame_map frames;

	// For unit buffering.
	std::cout.setf(std::ios::unitbuf);
	
	cv::Mat frame;
	for (uint i=0; i < faces.size(); i++) {
		std::cout << "    => Capturing image from camera " << i << " ... ";
		cv::VideoCapture cap(i+1);
		cap.set(CV_CAP_PROP_FRAME_WIDTH, dim);
		cap.set(CV_CAP_PROP_FRAME_HEIGHT, dim);
		cap >> frame;
		frames[faces[i]] = frame.clone();
		std::cout << "done." << std::endl;
	}

	std::cout.unsetf(std::ios::unitbuf);
	
	return frames;
}


/*
 * save_frames - Saves each frame as a jpg file.
 *
 * Parameters:
 *   frame_map frames := Each entry is the cube
 *     face and it's corresponding frame.
 *
 * Returns:
 *   None
 */
void enVR::save_frames(const frame_map& frames)
{
	for (auto it = frames.begin(); it != frames.end(); ++it)
		cv::imwrite("img/" + it->first + ".jpg", it->second);
}


/*
 * read_frames - Reads each frame from a jpg file.
 *
 * Returns:
 *   frame_map frames := Each entry is the cube face and its
 *     corresponding frame.
 */
frame_map enVR::read_frames()
{
	frame_map frames;
	for (auto it = faces.begin(); it != faces.end(); ++it) {
		cv::Mat frame = cv::imread("img/" + (*it) + ".jpg");
		cv::resize(frame, frames[(*it)], cv::Size(enVR::dim, enVR::dim));
	}
	return frames;
}
