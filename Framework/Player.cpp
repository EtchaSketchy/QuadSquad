#include "Player.h"

CPlayer::CPlayer()
{
	m_position = glm::vec3(0, 0, 0);
	m_scale = glm::vec3(1, 1, 1);
	objectName = 1;
}

CPlayer::~CPlayer()
{

}

void CPlayer::init(b2World &_world, glm::vec2 _position, glm::vec2 _dimensions, float _density, float _friction, float _resitution)
{
	//Make Vertex Array
	glGenVertexArrays(1, &VertexArrayObject);
	glBindVertexArray(VertexArrayObject);

	//Generate buffers 
	glGenBuffers(NUM_BUFFERS, BufferArrayObject);

	//manage position buffer
	glBindBuffer(GL_ARRAY_BUFFER, BufferArrayObject[POSITION]);
	glBufferData(GL_ARRAY_BUFFER, vertices_box.size() * 4, &vertices_box.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	//manage texture/color buffer
	glBindBuffer(GL_ARRAY_BUFFER, BufferArrayObject[TEXTURE]);
	glBufferData(GL_ARRAY_BUFFER, uvBuffer.size() * 4, &uvBuffer.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	//unbind vertex array
	glBindVertexArray(0);


	//Step 1
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(_position.x, _position.y);
	bodyDef.fixedRotation = true;

	//Step 2
	RigidBody = _world.CreateBody(&bodyDef);

	//Step 3
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(_dimensions.x, _dimensions.y);
	m_scale = glm::vec3(_dimensions.x, _dimensions.y, 1);

	//Step 4
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = _density;
	fixtureDef.friction = _friction;
	fixtureDef.restitution = _resitution;
	fixtureDef.filter.maskBits = 0x0000;


	//step 5
	RigidBody->CreateFixture(&fixtureDef);
	RigidBody->SetUserData(&objectName);
}

void CPlayer::render(GLuint _shader, CCamera _camera)
{
	//What shader to use?
	glUseProgram(_shader);

	//Set position to box3D coordinates
	m_position = glm::vec3(RigidBody->GetPosition().x, RigidBody->GetPosition().y, 0);
	m_rotate = RigidBody->GetAngle();

	//Lets make our models matrix first
	m_positionMatrix = glm::translate(m_position);
	m_scaleMatrix = glm::scale(m_scale);
	m_modelMatrix = m_positionMatrix * m_scaleMatrix;

	//rotate the model I guess?
	m_modelMatrix = glm::rotate(m_modelMatrix, m_rotate, glm::vec3(0, 0, 1));

	//Now lets make that sweet MVP matrix
	glm::mat4 mvp = _camera.projectionMatrix * _camera.viewMatrix * m_modelMatrix;

	//enable blend
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//and now hand it over to our shader to use
	GLuint MatrixID = glGetUniformLocation(_shader, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

	//Bind which texture to draw
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	//Draw the polys
	glBindVertexArray(VertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);

	//Now draw the weapon
	if (m_weapon != NULL)
	{
		m_weapon->render(_shader, _camera);
	}
}

void CPlayer::addSprite(char * imagepath)
{
	std::cout << std::endl << "ADDING SPRITE TO ARENA" << std::endl;
	glGenTextures(1, &m_texture);
	int width, height;
	unsigned char * IMAGEDATA;

	IMAGEDATA = SOIL_load_image(imagepath, &width, &height, 0, SOIL_LOAD_RGBA);
	std::cout << "RESULT: " << SOIL_last_result() << std::endl;

	//NOW THE TRICKY PART.
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	//TEXTURE PARAMETERS SHOULD HAPPEN BEFORE THE TEXIMAGE (SO HERE).
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, IMAGEDATA);
}

void CPlayer::addGamepad(CGamepad &_Gamepad)
{
	gamePad = &_Gamepad;
}

GLuint* CPlayer::GetVAO()
{
	return &VertexArrayObject;
}

GLuint* CPlayer::GetBAO(int _num)
{
	return &BufferArrayObject[_num];
}

b2Body* CPlayer::GetRigidBody()
{
	return RigidBody;
}

GLuint* CPlayer::GetBAOArray()
{
	return BufferArrayObject;
}

void CPlayer::update(float _deltaTime)
{
	//Update ps4 controller
	gamePad->update();

	//Update the players weapon
	if (m_weapon != NULL)
	{
		if (!gamePad->Rstick_Dead())
		{
			//First, subtract the pivot point
			//m_weapon->setPosition(glm::vec3(RigidBody->GetPosition().x, RigidBody->GetPosition().y, 1));

			//Now do its rotations....the hard part
			float rotation = atan2(gamePad->RightStick_y(), gamePad->RightStick_x());
			m_weapon->setRotation(rotation);
		}

		//And then set its position to where we want it to be
		m_weapon->setPosition(glm::vec3(RigidBody->GetPosition().x, RigidBody->GetPosition().y, 1));

		if (gamePad->isButtonPressed(gamePad->BUTTON_RBUMPER))
		{
			glm::vec2 direction(gamePad->RightStick_x(), gamePad->RightStick_y());
			m_weapon->fire(bullets, *RigidBody->GetWorld(),glm::vec2(RigidBody->GetPosition().x, RigidBody->GetPosition().y), direction);
		}

	}

	if (!gamePad->LStick_Dead())
	{
		//Get left stick inputs
		glm::vec2 values(gamePad->LeftStick_x(), gamePad->LeftStick_y());
		values = values * 100.0f * _deltaTime;

		b2Vec2 input(values.x, values.y);
		RigidBody->SetLinearVelocity(input);
	}
	else if(gamePad->LStick_Dead())
	{
		b2Vec2 input(0,0);
		RigidBody->SetLinearVelocity(input);
		RigidBody->SetLinearVelocity(input);
	}

	//std::cout << bullets.size() << std::endl;
}

void CPlayer::Equip(CWeapon & _weapon)
{
	m_weapon = &_weapon;
}

void CPlayer::setPosition(glm::vec3 _Position)
{
	m_position = _Position;
}

void CPlayer::setScale(glm::vec3 _Scale)
{
	m_scale = _Scale;
}
