#ifndef SHADERLOADER_H
#define SHADERLOADER_H

#include <string>
#include <fstream>
#include <vector>
#include "Dependencies\Glew\GL\glew.h"
#include "Dependencies\Freeglut\include\GL\glut.h"

class CShaderLoader
{
public:
	CShaderLoader();
	~CShaderLoader();

	//load the shaders
	GLuint loadShaders(const char * _vertexShader, const char * _fragmentShader);

private:

};


#endif