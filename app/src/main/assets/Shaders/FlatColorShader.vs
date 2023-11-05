#version 300 es
layout(location = 0) in vec3 aPos;

uniform mat4 u_Transform;
uniform mat4 u_ViewProjection;

void main()
{
    gl_Position = u_ViewProjection * u_Transform * vec4(aPos, 1.0);
}
