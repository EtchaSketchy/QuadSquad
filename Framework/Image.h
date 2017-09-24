#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <vector>
#include <string>
#include "Dependencies\soil\SOIL.h"
#include "Dependencies\Glew\GL\glew.h"
#include "Dependencies\Freeglut\include\GL\freeglut.h"
#include "Dependencies\GLM\glm\glm.hpp"
#include "Dependencies\GLM\glm\gtx\transform.hpp"
#include "Dependencies\GLM\glm\gtc\quaternion.hpp"
#include "Dependencies\soil\SOIL.h"
#include "Camera.h"

class CImage
{
public:
	CImage();
	~CImage();

	//Start up functions
	virtual void init();
	virtual void render(GLuint _shader, CCamera _camera);
	virtual void addSprite(char * imagepath);

	//Modify
	virtual void SetScale(glm::vec3 _val);
	virtual void SetPosition(glm::vec3 _val);

private:
	//enum used to identify buffers
	enum { POSITION, TEXTURE, NUM_BUFFERS };

	//userData
	int objectName;

	//Holds where we want the object to be
	glm::vec3 m_position;
	glm::vec3 m_scale;
	float m_rotate;

	//The actual matrices tp display where they are
	glm::mat4 m_rotationMatrix;
	glm::mat4 m_scaleMatrix;
	glm::mat4 m_positionMatrix;
	glm::mat4 m_modelMatrix;

	//Binds
	GLuint VertexArrayObject;
	GLuint BufferArrayObject[NUM_BUFFERS];

	//texutre
	GLuint m_texture;

	//UVs
	std::vector<GLfloat> uvBuffer
	{
		//FRONT FACE
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,

		0.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
	};

	//Vertices
	std::vector<GLfloat> vertices_box =
	{
		//front face
		1.0f, -1.0f ,1.0f,
		1.0f ,1.0f ,1.0f,
		-1.0f ,1.0f ,1.0f,
		1.0f ,-1.0f ,1.0f,
		-1.0f, 1.0f ,1.0f,
		-1.0f ,-1.0f ,1.0f,
	};
};




#endif