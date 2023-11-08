#version 410

layout (location = 0) in vec3 pos;
layout (location = 2) in vec3 normal;

uniform mat4 mvp;
uniform mat4 mv;

uniform float count;

out vec3 fragNormal;
out vec4 cs_position;

void main()
{
    vec3 position = pos + vec3(count * 2, 1.0, 1.0);
    gl_Position = mvp * vec4(position, 1.0);
    fragNormal = normal;

    cs_position = mv * vec4(position, 1.0);
}
