#include <algorithm>
#include "Viewer.hpp"

#define ESC 27

using namespace enVR;

static void display();
static void init();
static void keyboard_handler();

static point_set pts;
static GLdouble theta[] = {0.0, 0.0, 0.0};

void init_viewer(int* argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard_handler);
	glEnable(GL_DEPTH_TEST);
	glutCreateWindow("enVR");
	glutFullScreen();
	init();
}

void view_3d_image(point_set pset)
{
	std::copy(pset.begin(), pset.end(), std::back_inserter(pts));
	glutMainLoop();
}

static void init()
{
	glClearColor(0.9, 0.9, 1.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100, 600, -100, 600, 600, -100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

static void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);

	glRotated(theta[0], 250,   0,   0);
	glRotated(theta[1],   0, 250,   0);
	glRotated(theta[2],   0,   0, 250);

	glBegin(GL_POINTS);
	for (auto it = pts.begin(); it != pts.end(); ++it) {
		glVertex3f((*it)[0], (*it)[1], (*it)[2])
	}
	glEnd();

	glFlush();
	glutSwapBuffers();
}

static void keyboard_handler(unsigned char key, int x, int y)
{
	switch(key) {
		case 'w':
		theta[0] -= 1.0;
		break;

		case 's':
		theta[0] += 1.0;
		break;

		case 'a':
		theta[1] -= 1.0;
		break;

		case 'd':
		theta[1] += 1.0;
		break;

		case 'q':
		theta[2] -= 1.0;
		break;

		case 'e':
		theta[2] += 1.0;
		break;
		
		case ESC:
		glutLeaveMainLoop();
		return;
	}
	glutPostRedisplay();
}
