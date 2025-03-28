#version 330 core

layout (location = 0) in vec3 iPos;
layout (location = 1) in vec4 iColor;
layout (location = 2) in vec2 iTexCord;

out vec4 vColor;
out vec2 vTexCord;

void main(){
	gl_Position = vec4(iPos, 1.0);
	vColor = iColor;
	vTexCord = iTexCord;
}
