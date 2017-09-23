#include <iostream>
#include <chrono>
#include "ShaderLoader.h"
#include "Cube.h"
#include "Controls.h"


using namespace std;

//CAMERA
CCamera camera;

//Shaders
GLuint SHADER_DEFAULT;

//Gamepad
CControls gamePad;

//

//DeltaTime
float deltaTime;
auto t2 = std::chrono::high_resolution_clock::now();

//Render loop
void render()
{
	//clear all
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClearColor(0.08f, 0.08f, 0.08f, 0.0);

	//Swap out the buffers
	glutSwapBuffers();
}

//Game logic loop
void update()
{
	//DeltaTime Update
	auto t1 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> fp_ms = t1 - t2;
	deltaTime = fp_ms.count();
	deltaTime = deltaTime * 0.001f;
	t2 = t1;

	//update camera and controls
	//camera.update();

	cout << deltaTime << endl;

	glutPostRedisplay();
}

void mouseMovement(int xPos, int yPos)
{
	//Reset mouse position to centre of screen
	if (xPos >= (glutGet(GLUT_WINDOW_WIDTH) / 2) + 0.1 || xPos <= (glutGet(GLUT_WINDOW_WIDTH) / 2) - 0.1 || yPos >= (glutGet(GLUT_WINDOW_HEIGHT)/2) + 0.1 || yPos <= (glutGet(GLUT_WINDOW_HEIGHT) / 2) - 0.1)
	{
		glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	}
	
}

void KeyboardDown(unsigned char key, int x, int y)
{

}

void KeyboardUp(unsigned char key, int x, int y)
{

}

void init()
{
	//Make the shaders
	CShaderLoader shaderLoader;
	SHADER_DEFAULT = shaderLoader.loadShaders("Assets/vertex_default.vs","Assets/fragment_default.fs");

	//make camera
	camera.init();

	//enable depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//enable Back Face Culling
	glEnable(GL_CULL_FACE);

	//enable anti-aliasing
	glEnable(GL_MULTISAMPLE);

	//enable stencil
	glEnable(GL_STENCIL_TEST);

	//hide mouse
	glutSetCursor(GLUT_CURSOR_NONE);

}

//Entry point for everything
int main(int argc, char **argv)
{
	//init glut and make window
	glutInit(&argc, argv);
	glutInitWindowPosition(1200, 1);
	glutInitWindowSize(800, 800);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE | GLUT_STENCIL);
	glutCreateWindow("QuadSquad");

	//initate glew
	glewInit();

	//initiate
	init();

	//register callbacks
	glutDisplayFunc(render);
	glutIdleFunc(update);
	glutPassiveMotionFunc(mouseMovement);
	glutKeyboardFunc(KeyboardDown);
	glutKeyboardUpFunc(KeyboardUp);

	//enter loop
	glutMainLoop();
}