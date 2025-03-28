#version 330 core

in vec4 vColor;
in vec2 vTexCord;

out vec4 fColor;

uniform sampler2D tex;

void main(){
	fColor = mix(texture(tex, vTexCord), vec4(vColor.rgb,1.0), vColor.a);
}
