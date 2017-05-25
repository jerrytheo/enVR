/*
 * main.cpp - Main function for enVR.
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

#include "enVRConsts.hpp"
#include "Capture.hpp"
#include "Generate.hpp"
#include "Viewer.hpp"

#include <iostream>
#include <limits>

const uchar rthresh[] = {0, 200};
const uchar gthresh[] = {0, 200};
const uchar bthresh[] = {0, 200};

int main(int argc, char* argv[])
{
	using std::cout;
	using std::endl;
	using std::cin;

	uint count_cameras();

	unsigned char choice = 'n';

	cout << endl;

	cout << "enVR  Copyright (C) 2017  Abhijit J. Theophilus, Abhishek S. V." << endl;
	cout << "This program comes with ABSOLUTELY NO WARRANTY; This is free software," << endl;
    cout << "and you are welcome to redistribute it under certain conditions." << endl;
	cout << "For the complete license, see LICENSE.md." << endl;

	cout << endl;

	cout << "Welcome to enVR" << endl;
	cout << "---------------" << endl;
	
	cout << endl;

	cout << "Author information:" << endl;
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
