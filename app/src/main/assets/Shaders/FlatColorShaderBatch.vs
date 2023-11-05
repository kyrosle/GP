#version 300 es
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec2 aOffset;

uniform mat4 u_Transform;
uniform mat4 u_ViewProjection;

out vec2 Tex;

void main()
{
    gl_Position = u_ViewProjection * u_Transform * vec4(aPos + vec3(aOffset, 0.0), 1.0);
    Tex = aTex;
}
