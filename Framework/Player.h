#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <string>
#include "Dependencies\soil\SOIL.h"
#include "Dependencies\Glew\GL\glew.h"
#include "Dependencies\Freeglut\include\GL\freeglut.h"
#include "Dependencies\GLM\glm\glm.hpp"
#include "Dependencies\GLM\glm\gtx\transform.hpp"
#include "Dependencies\GLM\glm\gtc\quaternion.hpp"
#include "Dependencies\GLM\glm\gtx\quaternion.hpp"
#include "Dependencies\soil\SOIL.h"
#include "Camera.h"
#include "Box2D.h"
#include "Controls.h"
#include "Player.h"
#include "PS4.h"
#include "Weapon.h"
#include "Bullet.h"


class CWeapon;

class CPlayer
{
public:
	CPlayer();
	~CPlayer();

	//Start up functions
	virtual void init(b2World &_world, glm::vec2 _position, glm::vec2 _dimensions, float _density, float _friction, float _resitution);
	virtual void render(GLuint _shader, CCamera _camera);
	virtual void addSprite(char * imagepath);
	virtual void addGamepad(CGamepad &Gamepad);

	//Get information
	virtual GLuint* GetVAO();
	virtual GLuint* GetBAO(int _num);
	virtual b2Body* GetRigidBody();
	virtual GLuint* GetBAOArray();

	//updates
	virtual void update(float _deltaTime);
	virtual void Equip(CWeapon& _weapon);


	//movement
	virtual void setPosition(glm::vec3 _Position);
	virtual void setScale(glm::vec3 _Scale);

	//Bullets
	std::vector<CBullet> bullets;

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

	//Rigidbody
	b2Body* RigidBody;

	//Current weapon
	CWeapon* m_weapon;

	//Controller
	CGamepad* gamePad;
};


#endif