#version 330 core
in vec2 TexCoord;

uniform sampler2D texture0;
uniform vec3 lightColor;

out vec4 FragColor;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    FragColor = texture2D(texture0, TexCoord) * vec4(ambient, 1.0f);
}
