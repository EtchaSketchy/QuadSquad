#include <iostream>
#include "Dependencies\Freeglut\include\GL\glut.h"
using namespace std;

//Render loop
void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(0.0, 0.5, 0.0);
	glEnd();

	glutSwapBuffers();
}

//Game logic loop
void update()
{
	
}

//Entry point for everything
int main(int argc, char **argv)
{
	//init glut and make window
	glutInit(&argc, argv);
	glutInitWindowPosition(1, 1);
	glutInitWindowSize(400, 400);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("QuadSquad");

	//register callbacks
	glutDisplayFunc(render);
	glutIdleFunc(update);

	//enter loop
	glutMainLoop();

	Sleep(5000);
}