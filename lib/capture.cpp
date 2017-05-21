#include "capture.hpp"

/*
 * capture_images - Captures images sequentially from each of the
 * cameras attached and returns an std::map that associates each image
 * with the camera attached.
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   std::map<std::string, cv::Mat> := Associates the cube face with
 *     the captured image.
 */

std::map<std::string, cv::Mat> capture_images()
{
	using std::string;
	std::map<string, cv::Mat> frames;
	std::vector<string> cams {"front", "left", "right", "back"};

	// For unit buffering.
	std::cout.setf(std::ios::unitbuf);
	
	cv::Mat frame;
	for (int i=0; i < cams.size(); i++) {
		std::cout << "Capturing image from camera " << i << " ... ";
		cv::VideoCapture cap(i+1);
		cap.set(CV_CAP_PROP_FRAME_WIDTH, DIM);
		cap.set(CV_CAP_PROP_FRAME_HEIGHT, DIM);
		cap >> frame;
		frames[cams[i] = frame.clone();
		std::cout << "done." << std::endl;
	}

	std::cout.unsetf(std::ios::unitbuf);
	
	return frames;
}


/*
 * save_frames - Saves each frame as a jpg file.
 *
 * Parameters:
 *   std::map<std::string, cv::Mat> frames := Each entry is the cube
 *     face and it's corresponding frame.
 *
 * Returns:
 *   None
 */
void save_frames(std::map<std::string, cv::Mat> frames)
{
	for (auto it = frames.begin(); it != frames.end(); ++it)
		cv::imwrite("img/" + it->first + ".jpg", it->second);
}
