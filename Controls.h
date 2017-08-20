#ifndef CONTROLS_H
#define CONTROLS_H

#include "Dependencies\Glew\GL\glew.h"
#include "Dependencies\Freeglut\include\GL\glut.h"
#include "Dependencies\GLM\glm\glm.hpp"
#include "Dependencies\GLM\glm\gtc\matrix_transform.hpp"
#include "Camera.h"

class CControls
{
public:
	CControls();
	~CControls();

	void init(CCamera *camera);
	void update(float _deltatime);
	void mouseUpdate(float _deltatime, int xPos, int yPos);
	void keyDown(float _deltatime, unsigned char key);
	void keyUp(float _deltatime, unsigned char key);

private:
	float horizontalAngle;
	float verticalAngle;
	float FieldOfView;

	float speed;
	float mouseSpeed;

	//ourCamera we're changing
	CCamera *m_camera;

	//Values
	glm::vec3 m_direction;
	glm::vec3 m_up;
	glm::vec3 m_right;

	//keyboard
	bool m_keyboard[256];
};

#endif