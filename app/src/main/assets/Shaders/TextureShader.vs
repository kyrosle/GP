#version 300 es
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTex;

out vec2 TexCoord;

uniform mat4 u_Transform;
uniform mat4 u_ViewProjection;

void main()
{
    gl_Position = u_ViewProjection * u_Transform * vec4(aPos, 1.0);
    TexCoord = aTex;
}
