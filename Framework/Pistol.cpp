#include "Pistol.h"

CPistol::CPistol()
{
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
		_bullets.push_back(CBullet(_world, _position, _direction, glm::vec2(0.3, 0.3), 2.5f, 1.3f, 0.1f));
		fireRate = 1.0f;
	//}
	
}
