#version 300 es

in vec2 TexCoord;

out vec4 color;
uniform sampler2D u_Texture2;

void main()
{
    color = texture(u_Texture2, TexCoord);
}
