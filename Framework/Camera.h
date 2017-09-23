#ifndef CAMERA_H
#define CAMERA_H

#include "Dependencies\Glew\GL\glew.h"
#include "Dependencies\Freeglut\include\GL\glut.h"
#include "Dependencies\GLM\glm\glm.hpp"
#include "Dependencies\GLM\glm\gtc\matrix_transform.hpp"

class CCamera
{
public:
	CCamera();
	~CCamera();

	void init();
	void update();

	//matrices that are handed to the object
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	//movement
	void setPosition(glm::vec3 _position);
	void setDirection(glm::vec3 _direction);

private:


	//Camera information
	glm::vec3 m_position;
	glm::vec3 m_direction;
};

#endif