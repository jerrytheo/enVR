#include "enVRConsts.hpp"
#include "Capture.hpp"
#include "Generate.hpp"
#include "Viewer.hpp"

#include <iostream>
#include <limits>

const uchar rthresh = 200;
const uchar gthresh = 200;
const uchar bthresh = 200;

int main(int argc, char* argv[])
{
	using std::cout;
	using std::endl;
	using std::cin;

	uint count_cameras();

	unsigned char choice = 'n';

	cout << endl;
	
	cout << "Welcome to enVR" << endl;
	cout << "---------------" << endl;
	
	cout << endl;

	cout << "Developed by:" << endl;
	cout << "  Abhijit J. Theophilus  (abhitheo96@gmail.com)" << endl;
	cout << "  Abhishek Surbhat       (abhishek.surbhat@gmail.com)" << endl;
	
	cout << endl;
	
	uint cams = count_cameras();
	cout << "Cameras attached: " << cams << endl;
	if (cams >= 6) {
		cout << ":: Proceed to capture images? [y/n] ";
		cin  >> choice;
	}

	cout.setf(std::ios::unitbuf);

	enVR::frame_map frames;
	if (choice == 'y') {
		cout << ":: Ignoring camera 1." << endl;
		cout << ":: Capturing images." << endl;
		frames = enVR::capture_images();
		cout << ":: Saving frames to img ... ";
		enVR::save_frames(frames);
		cout << "done." << endl;
	} else {
		cout << ":: Retrieving images from img ... ";
		frames = enVR::read_frames();
		cout << "done." << endl;
	}

	cout << ":: Extrapolating projections." << endl;
	enVR::point_map pmap;
	for (auto it = enVR::faces.begin(); it != enVR::faces.end(); ++it) {
		cout << "    => Extrapolating " << *it << " ... ";
		pmap[(*it)] = enVR::extrapolate_projection(frames[(*it)], (*it),
												   rthresh, gthresh, bthresh);
		cout << "done." << endl;
	}

	cout << ":: Constructing 3D image ... ";
	enVR::point_set img3d = enVR::construct_3d_image(pmap);
	cout << "done." << endl;

	cout << ":: Initializing OpenGL viewer ... ";
	enVR::init_viewer(&argc, argv);
	cout << "done." << endl;

	cout << ":: Reached target: Viewer." << endl;
	enVR::view_3d_image(img3d);
}

/* count_cameras - Count the number of cameras attached. */
uint count_cameras()
{
	cv::VideoCapture temp_camera;
	uint maxTested = 10;
	for (uint i = 0; i < maxTested; i++) {
		cv::VideoCapture temp_camera(i);
		bool res = (!temp_camera.isOpened());
		temp_camera.release();
		if (res)
			return i;
	}
	return maxTested;
}
