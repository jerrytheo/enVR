#include "PointGen.hpp"

#include <GL/glut.h>
#include <vector>
#include <iostream>

std::vector<GLfloat*> pts;

void display(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POINTS);
	glColor3f(0.0, 0.0, 0.0);
    for (std::vector<GLfloat*>::iterator it=pts.begin(); it != pts.end(); ++it) {
        glVertex2f((*it)[0], (*it)[1]);
    }
	glEnd();
	glFlush();
	glutSwapBuffers();
}


void init()
{
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	glPointSize(1.0);
    pts = generate_points();
}


int main(int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("enVR");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
}
