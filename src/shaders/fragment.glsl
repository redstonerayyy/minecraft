#version 330 core
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture0;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

out vec4 FragColor;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor; 

    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * lightColor;
    
    FragColor = texture2D(texture0, TexCoord) * vec4(ambient + diffuse + specular, 1.0f);
}
