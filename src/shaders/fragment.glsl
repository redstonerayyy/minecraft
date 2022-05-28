#version 330 core
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture0;

out vec4 FragColor;

void main()
{
    FragColor = mix(texture(texture0, TexCoord), texture(texture1, TexCoord), 0.8);
}
