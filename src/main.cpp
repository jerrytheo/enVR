#include "Capture.hpp"
#include "Generate.hpp"
#include "Viewer.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
	unsigned char choice;

	cout << endl;
	
	cout << "Welcome to enVR" << endl;
	cout << "---------------" << endl;
	
	cout << endl;

	cout << "Developed by:" << endl;
	cout << "  Abhijit J. Theophilus  (abhitheo96@gmail.com)" << endl;
	cout << "  Abhishek Surbhat       (abhishek.surbhat@gmail.com)" << endl;
	
	cout << endl;
	
	cout << "Cameras attached: 6" << endl;
	cout << ":: Proceed to capture images? [y/n] ";
	cin  >> ch;
	if (ch == 'y') {
		cout << ":: Ignoring camera 1." << endl;
		cout << ":: Beginning captures." << endl;
		auto frames = enVR::capture_images();
		cout << ":: Captures complete." << endl;
		cout << ":: Saving frames to img." << endl;
		enVR::save_frames(frames);
		cout << ":: Save complete." << endl;
	} else {
		cout << ":: Retrieving images from img." << endl;
		auto frames = enVR::read_frames();
		cout << ":: Frames retrieved." << endl;
	}
}
