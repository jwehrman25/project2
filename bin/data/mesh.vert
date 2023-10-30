#version 410

layout (location = 0) in vec3 pos;
layout (location = 3) in vec2 uv;

uniform mat4 mvp;
uniform mat4 mv;

uniform float count;

out vec2 fragUV;
out vec4 cs_position;

void main()
{
	//gl_Position = mvp * vec4(pos + vec3(count * 2, 1.0, 1.0), 1.0);
	//fragUV = uv;
	gl_Position = mvp * vec4(pos, 1.0);
	fragUV = uv;

	cs_position = mv * vec4(pos, 1.0);
}