#include "Cube.h"



GLfloat texCoord[] =
{
	0.0f, 0.0f,  // lower-left corner  
	1.0f, 0.0f,  // lower-right corner
	1.0f, 1.0f  // top-center corner
};


CCube::CCube()
{
	m_position = glm::vec3(0, 0, 0);
	m_scale = glm::vec3(1, 1, 1);
	m_aim = glm::vec3(0, 1, 0);
}

CCube::~CCube()
{
}

void CCube::init()
{
	//Generate the vertex array
	glGenVertexArrays(1, &VertexArrayObject);
	glBindVertexArray(VertexArrayObject);

	//generate the position buffer
	glGenBuffers(1, &BufferArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER,BufferArrayObject);

	//buffer position data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

void CCube::render(GLuint _shader, CCamera _camera)
{
	//Lets make our models matrix first
	m_positionMatrix = glm::translate(m_position);
	m_scaleMatrix = glm::scale(m_scale);
	m_modelMatrix = m_positionMatrix * m_scaleMatrix;

	//Now lets make that sweet MVP matrix
	glm::mat4 mvp = _camera.projectionMatrix * _camera.viewMatrix * m_modelMatrix;

	//and now hand it over to our shader to use
	GLuint MatrixID = glGetUniformLocation(_shader, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

	//What shader to use?
	glUseProgram(_shader);
	

	glBindVertexArray(VertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, 12*3);
	glBindVertexArray(0);

	//And then lets very sneakily render some bullet! (NEED TO FIX THIS)
	if (m_bullets.size() != 0)
	{
		for (unsigned int i = 0; i < m_bullets.size(); i++)
		{
			m_bullets[i].render(_shader, _camera);
		}
	}
}

void CCube::setTexture()
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//generate and load texture
	int width, height;

	unsigned char *m_texture = SOIL_load_image("Assets\Textures.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_texture);
}

void CCube::setPosition(glm::vec3 _Position)
{
	m_position = _Position;
}

void CCube::setScale(glm::vec3 _Scale)
{
	m_scale = _Scale;
}

void CCube::update(CGamepad & _controller, float _deltaTime)
{
	//Update controller
	_controller.update();

	//Movement
	if (!_controller.LStick_Dead())
	{		
		//make a vector to move towards
		m_position += glm::vec3(_controller.LeftStick_x(), _controller.LeftStick_y(), m_position.z);
	}

	//Aiming
	if (!_controller.Rstick_Dead())
	{
		//Make a vector to aim at
		m_aim = glm::vec3(_controller.RightStick_x(), _controller.RightStick_y(), m_position.z);
	}
	
	//Shootings
	if (_controller.isButtonPressed(9))
	{
			m_bullets.push_back(CBullet(m_aim, m_position));
			_controller.Vibrate(1.0f, 1.0f);
			m_isFired = true;


	}
	else
	{
		_controller.Vibrate(0.0f, 0.0f);
	}

	//update the bullet
	if (m_bullets.size() != 0)
	{
		for (unsigned int i = 0; i < m_bullets.size(); i++)
		{
			m_bullets[i].update(_deltaTime);
		}
	}
}
