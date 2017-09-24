#include "Camera.h"

CCamera::CCamera()
{
	m_position = glm::vec3(0, 0, 10);
	m_direction = glm::vec3(0, 0, 0);
}

CCamera::~CCamera()
{
}

void CCamera::init()
{
	//make our projection matrix
	//projectionMatrix = glm::perspective(glm::radians(45.0f), (float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT), 0.1f, 100.0f);
	projectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f);
	//make view matrix
	viewMatrix = glm::lookAt
	(
		glm::vec3(0, 0, 10),	//Camera is where now?
		glm::vec3(0, 0, 0),	//Camera looks at what now?
		glm::vec3(0, 1, 0)	//Camera head is what way now?
	);
}

void CCamera::update()
{
	float aspectRatio = (float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT);

	if (glutGet(GLUT_WINDOW_WIDTH) >= glutGet(GLUT_WINDOW_HEIGHT))
	{
		projectionMatrix = glm::ortho(-10.0f * aspectRatio, 10.0f * aspectRatio, -10.0f, 10.0f, 0.0f, 100.0f);
	}
	else
	{
		projectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f / aspectRatio, 10.0f / aspectRatio, 0.0f, 100.0f);
	}


	viewMatrix = glm::lookAt
	(
		glm::vec3(0, 0, 10),	//Camera is where now?
		glm::vec3(0, 0, 0),	//Camera looks at what now?
		glm::vec3(0, 1, 0)	//Camera head is what way now?
	);
}

void CCamera::setPosition(glm::vec3 _position)
{
	m_position += (_position);
}

void CCamera::setDirection(glm::vec3 _direction)
{
	m_direction = _direction;
}
