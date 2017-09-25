#include "Pistol.h"

CPistol::CPistol()
{
	//this works just need to scale the guns to the right size...
	/*
	int temp = rand() % 5;
	if (temp == 0)
	{
		addSprite("Assets/Textures/Weapons/Gun.psd");
	}
	else if (temp == 1)
	{
		addSprite("Assets/Textures/Weapons/Gun1.png");
	}
	else if (temp == 2)
	{
		addSprite("Assets/Textures/Weapons/Gun2.png");
	}
	else if (temp == 3)
	{
		addSprite("Assets/Textures/Weapons/Gun3.png");
	}
	else
	{
		addSprite("Assets/Textures/Weapons/Gun4.png");
	}*/

	addSprite("Assets/Textures/Weapons/Gun.psd");
	fireRate = 0;
}

CPistol::~CPistol()
{
}

void CPistol::fire(std::vector<CBullet>& _bullets, b2World &_world, glm::vec2 _position, glm::vec2 _direction)
{
	//Spawn a bullet
	//if (fireRate <= 0)
	//{

	//add the neutral aim stick here--------------
	//if stick is not moving, either aim at the last targeted place or don't shoot at all

		_bullets.push_back(CBullet(_world, _position, _direction, glm::vec2(0.3, 0.3), 2.5f, 1.3f, 0.1f));
		fireRate = 1.0f;
	//}
	

		//lastBulletFired = glm::vec2(_direction.x, _direction.y);
}
