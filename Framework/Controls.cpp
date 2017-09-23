#include "Controls.h"

CControls::CControls()
{
	horizontalAngle = 3.14f;
	verticalAngle = 0.0f;
	FieldOfView = 45.0f;
	speed = 0.01f;
	mouseSpeed = 0.00005f;
}

CControls::~CControls()
{
}

void CControls::init(CCamera *camera)
{
	m_camera = camera;
}

void CControls::update(float _deltatime)
{
	//Set direction...
	m_camera->setDirection(m_direction);

	//Now we can do movement
	//move forward and back
	if (m_keyboard['w'] == true)
	{
		m_camera->setPosition(glm::normalize(m_direction) * _deltatime * speed);
	}
	else if (m_keyboard['s'] == true)
	{
		m_camera->setPosition(glm::normalize(m_direction) * _deltatime * -speed);
	}

	//move left and right
	if (m_keyboard['a'] == true)
	{
		m_camera->setPosition(glm::normalize(m_right) * _deltatime * -speed);
	}
	else if (m_keyboard['d'] == true)
	{
		m_camera->setPosition(glm::normalize(m_right) * _deltatime * speed);
	}

	//move rtue up and down
	if (m_keyboard['q'] == true)
	{
		m_camera->setPosition(glm::vec3(0,1,0) * _deltatime * -speed);
	}
	else if (m_keyboard['e'] == true)
	{
		m_camera->setPosition(glm::vec3(0, 1, 0) * _deltatime * speed);
	}
}

void CControls::mouseUpdate(float _deltatime, int xPos, int yPos)
{
	//Compute our angles
	horizontalAngle += mouseSpeed * _deltatime * float(glutGet(GLUT_WINDOW_WIDTH) / 2 - xPos);
	verticalAngle += mouseSpeed * _deltatime * float(glutGet(GLUT_WINDOW_HEIGHT) / 2 - yPos);

	//now calculate in world space where we are looking
	glm::vec3 direction
	(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	//now calculate the "right" vector
	glm::vec3 right
	(
		sin(horizontalAngle - 3.14f/2.0f),
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);

	//now we can calculate the up vector using cross
	glm::vec3 up = glm::cross(right, direction);

	
	m_direction = direction;
	m_right = right;
	m_up = up;
}

void CControls::keyDown(float _deltatime, unsigned char key)
{
	//checks I guess
	m_keyboard[key] = true;
}

void CControls::keyUp(float _deltatime, unsigned char key)
{
	//checks I guess
	m_keyboard[key] = false;
}
