#include "Image.h"

CImage::CImage()
{
	m_position = glm::vec3(0,0,0);
	m_scale = glm::vec3(-10, -10, 3);
}

CImage::~CImage()
{
}

void CImage::init()
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

}

void CImage::render(GLuint _shader, CCamera _camera)
{
	//What shader to use?
	glUseProgram(_shader);

	//Lets make our models matrix first
	m_positionMatrix = glm::translate(m_position);
	m_scaleMatrix = glm::scale(m_scale);
	m_modelMatrix = m_positionMatrix * m_scaleMatrix;

	//Now lets make that sweet MVP matrix
	glm::mat4 mvp = _camera.projectionMatrix * _camera.viewMatrix * m_modelMatrix;

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
}

void CImage::addSprite(char * imagepath)
{
	std::cout << std::endl << "ADDING SPRITE TO ARENA" << std::endl;
	glGenTextures(1, &m_texture);
	int width, height;
	unsigned char * IMAGEDATA;

	IMAGEDATA = SOIL_load_image(imagepath, &width, &height, 0, SOIL_LOAD_AUTO);
	std::cout << "RESULT: " << SOIL_last_result() << std::endl;

	//NOW THE TRICKY PART.
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	//TEXTURE PARAMETERS SHOULD HAPPEN BEFORE THE TEXIMAGE (SO HERE).
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, IMAGEDATA);
}

void CImage::SetScale(glm::vec3 _val)
{
	m_scale = _val;
}

void CImage::SetPosition(glm::vec3 _val)
{
	m_position = _val;
}
