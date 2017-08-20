#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include "Camera.h"
#include "Dependencies\Glew\GL\glew.h"
#include "Dependencies\Freeglut\include\GL\glut.h"
#include "Dependencies\GLM\glm\glm.hpp"
#include "Dependencies\GLM\glm\gtx\transform.hpp"
#include "Dependencies\soil\SOIL.h"
#include "PS4.h"
#include "Bullet.h"

class CCube
{
public:
	CCube();
	~CCube();

	//Start up functions
	void init();
	void render(GLuint _shader, CCamera _camera);
	void setTexture();

	//movement
	void setPosition(glm::vec3 _Position);
	void setScale(glm::vec3 _Scale);

	//update
	void update(CGamepad & _controller,float _deltaTime);

private:
	//Holds where we want the object to be
	glm::vec3 m_position;
	glm::vec3 m_scale;
	glm::vec3 m_aim;

	//bool
	bool m_isFired;
	float timer;

	//bullet
	std::vector<CBullet> m_bullets;

	//The actual matrices tp display where they are
	glm::mat4 m_scaleMatrix;
	glm::mat4 m_positionMatrix;
	glm::mat4 m_modelMatrix;

	//Binds
	GLuint VertexArrayObject;
	GLuint BufferArrayObject;
	GLuint TextureArrayObject;
	
	//texutre
	unsigned char* m_texture;

	//Vertices
	GLfloat vertex_data[108] = {
		-1.0f,-1.0f,-1.0f, // triangle 1 : begin
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, // triangle 1 : end
		1.0f, 1.0f,-1.0f, // triangle 2 : begin
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f, // triangle 2 : end
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};
};

#endif

