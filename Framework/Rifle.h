#ifndef RIFLE_H
#define RIFLE_H

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
#include "Box2D.h"
#include "Controls.h"
#include "Player.h"
#include "PS4.h"
#include "Weapon.h"
#include "Bullet.h"




class CRifle : public CWeapon
{
public:
	CRifle();
	~CRifle();

	virtual void fire(std::vector<CBullet>& _bullets, b2World &_world, glm::vec2 _position, glm::vec2 _direction) override;


private:
	float fireRate;
	glm::vec2 lastBulletFired;
};



#endif // !RIFLE_H
