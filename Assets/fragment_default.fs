#version 330 core

in vec2 Textcoord;
out vec3 fragment;

uniform sampler2D myTextureSampler;

void main(){
	//fragment = texture(myTextureSampler,Textcoord).rgba;
	fragment = vec3(1.0,0.0,0.0);
}