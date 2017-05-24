/*
 * Viewer.cpp - Functions to construct the viewer for the 3D mdoel.
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

#include <algorithm>
#include "Viewer.hpp"

#define ESC 27

using namespace enVR;

static void display();
static void init();
static void keyboard_handler(unsigned char, int, int);

static point_set pts;
static GLdouble theta[] = {0.0, 0.0, 0.0};


/*
 * init_viewer - Initializes the viewer by initializing GLUT.
 *
 * Parameters:
 *   int* argc := Command line arguments count.
 *   char** argv := Command line arguments.
 *
 * Returns:
 *   None.
 */
void enVR::init_viewer(int* argc, char** argv)
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("enVR");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard_handler);
	glEnable(GL_DEPTH_TEST);
	init();
}


/*
 * view_3d_image - Display the 3d model.
 *
 * Parameters:
 *   point_set pset := The set of points that form the 3D model.
 *
 * Returns:
 *   None.
 */
void enVR::view_3d_image(const point_set& pset)
{
	std::copy(pset.begin(), pset.end(), std::inserter(pts, pts.end()));
	glutMainLoop();
}


static void init()
{
	glClearColor(0.85, 0.85, 1.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100, enVR::dim+100, -100, enVR::dim+100, enVR::dim+100, -100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


static void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslated(enVR::dim/2, enVR::dim/2, enVR::dim/2);
	glRotated(theta[0], enVR::dim/2, 0, 0);
	glRotated(theta[1], 0, enVR::dim/2, 0);
	glRotated(theta[2], 0, 0, enVR::dim/2);
	glTranslated(-enVR::dim/2, -enVR::dim/2, -enVR::dim/2);

	glBegin(GL_POINTS);
	for (auto it = pts.begin(); it != pts.end(); ++it) {
		GLint x = (*it)[0];
		GLint y = (*it)[1];
		GLint z = (*it)[2];
		glColor3d(static_cast<double>(x) / enVR::dim,
				  static_cast<double>(y) / enVR::dim,
				  static_cast<double>(z) / enVR::dim);
		glVertex3i(x, y, z);
	}
	glEnd();

	glFlush();
	glutSwapBuffers();
}


static void keyboard_handler(unsigned char key, int x, int y)
{
	switch(key) {
		case 'w':
		theta[0] -= 10.0;
		break;

		case 's':
		theta[0] += 10.0;
		break;

		case 'a':
		theta[1] -= 10.0;
		break;

		case 'd':
		theta[1] += 10.0;
		break;

		case 'q':
		theta[2] -= 10.0;
		break;

		case 'e':
		theta[2] += 10.0;
		break;
		
		case ESC:
		glutLeaveMainLoop();
		return;
	}
	theta[0] = (theta[0] >= 360) ? 0 : theta[0];
	theta[1] = (theta[1] >= 360) ? 0 : theta[1];
	theta[2] = (theta[2] >= 360) ? 0 : theta[2];
	glutPostRedisplay();
}
