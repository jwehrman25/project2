#version 410

in vec3 fragNormal;
in vec4 cs_position;

uniform mat4 normal;

out vec4 outCol;

void main()
{
    float distToCamera = length(cs_position.xyz);

    vec3 worldNormal = mat3(normal) * fragNormal;

    outCol = vec4(fragNormal, 1.0);
    outCol.a = 1.0 - smoothstep(2.0, 8.0, distToCamera);
}
