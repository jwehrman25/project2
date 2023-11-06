#version 410

uniform sampler2D parrotTex;

in vec2 fragUV;
in vec4 cs_position;

out vec4 outCol;

void main()
{
    float distToCamera = length(cs_position.xyz);
	outCol = vec4(fragUV, 0.0, 1.0 - smoothstep(0.0, 10.0, distToCamera));
}