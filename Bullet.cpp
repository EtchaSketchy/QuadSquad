#include "Bullet.h"



CBullet::CBullet()
{

}

CBullet::CBullet(glm::vec3 _velocity, glm::vec3 _position)
{
	//Generate the vertex array
	glGenVertexArrays(1, &VertexArrayObject);
	glBindVertexArray(VertexArrayObject);

	//generate the position buffer
	glGenBuffers(1, &BufferArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, BufferArrayObject);

	//buffer position data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//assign velocity
	m_velocity = _velocity;

	//set position
	m_position = _position;
	m_scale = glm::vec3(0.25f, 0.25f, 0.25f);
}

CBullet::~CBullet()
{

}

void CBullet::update(float deltaTime)
{
	m_position += m_velocity * deltaTime * 24.0f;
}

void CBullet::render(GLuint _shader, CCamera camera)
{
	//Lets make our models matrix first
	m_positionMatrix = glm::translate(m_position);
	m_scaleMatrix = glm::scale(m_scale);
	m_modelMatrix = m_positionMatrix * m_scaleMatrix;

	//Now lets make that sweet MVP matrix
	glm::mat4 mvp = camera.projectionMatrix * camera.viewMatrix * m_modelMatrix;

	//and now hand it over to our shader to use
	GLuint MatrixID = glGetUniformLocation(_shader, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

	//What shader to use?
	glUseProgram(_shader);


	glBindVertexArray(VertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
	glBindVertexArray(0);
}
