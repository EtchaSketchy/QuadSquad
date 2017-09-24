#version 330 core

out vec4 fragment;

in vec3 TexCoords;

uniform samplerCube skybox;

void main(){
	//fragment = vec4(0.0f,0.7f,0.0f,1.0f);
	fragment = texture(skybox, TexCoords);
}