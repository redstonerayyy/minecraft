#version 330 core

in vec3 FragPos;
in vec2 TexCoord;
in vec3 Normal;

out vec4 FragColor;

uniform sampler2D tex_sampler1;
uniform vec3 lightPos;	
uniform vec3 viewPos;

void main()
{
	float ambientstrength = 0.5;
	vec3 lightcolor = vec3(1.0, 1.0, 1.0);
	vec3 ambient = ambientstrength * lightcolor;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(-lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightcolor;

	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
	vec3 specular = specularStrength * spec * lightcolor;

	vec4 result = vec4(specular, 1.0) * texture2D(tex_sampler1, TexCoord); 
    
	FragColor =  result;
}