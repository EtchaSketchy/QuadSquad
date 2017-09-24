#version 330 core
layout(location = 0) in vec3 Vertex_Position;
layout(location = 1) in vec2 Vertex_Texture;

uniform mat4 MVP;
out vec2 UVcoordinates;

void main()
{
		gl_Position = MVP * vec4(Vertex_Position,1);
		UVcoordinates = Vertex_Texture;

}