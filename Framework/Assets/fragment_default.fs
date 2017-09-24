#version 330 core

out vec4 fragment;
in vec2 UVcoordinates;

uniform sampler2D TextureSampler;

void main(){
	fragment = texture(TextureSampler,UVcoordinates).rgba;
	//fragment = vec4(1.0,0.0,0.0,0.0);
}