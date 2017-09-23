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
	viewMatrix = glm::lookAt
	(
		m_position,	//Camera is where now?
		m_position + m_direction,	//Camera looks at what now?
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
