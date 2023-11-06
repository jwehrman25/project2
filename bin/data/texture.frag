#version 410

uniform sampler2D parrotTex;

in vec2 fragUV;
in vec4 cs_position;

out vec4 outCol;

void main()
{
    float distToCamera = cs_position.z;
	//outCol = vec4(fragUV, 0.0, distToCamera);
	outCol = vec4(fragUV, 0.0, 1.0);
}