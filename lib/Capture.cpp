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
void enVR::save_frames(frame_map frames)
{
	for (auto it = frames.begin(); it != frames.end(); ++it)
		cv::imwrite("img/" + it->first + ".jpg", it->second);
}


/*
 * read_frames - Reads each frame from a jpg file.
 *
 * Returns:
 *   frame_map frames := Each entry is the cube
 *     face and it's corresponding frame.
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
