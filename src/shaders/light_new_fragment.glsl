#version 460 core

in vec3 FragPos;
in vec2 TexCoord;
in vec3 Normal;

out vec4 FragColor;

uniform sampler2D tex_sampler1;
uniform vec3 lightPos;	
uniform vec3 viewPos;

void main()
{
	vec3 norm = normalize(Normal);
	
	float ambientstrength = 0.2;
	vec3 lightcolor = vec3(1.0, 1.0, 1.0);
	vec3 ambient = ambientstrength * lightcolor;


	vec3 lightDir = normalize(-lightPos - FragPos);
	vec3 diffDir = normalize(lightPos - FragPos);
	float diff = max(dot(diffDir, norm), 0.0);
	vec3 diffuse = diff * lightcolor;

	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
	vec3 specular = specularStrength * spec * lightcolor;

	vec4 result = vec4(ambient + diffuse + specular, 1.0) * texture(tex_sampler1, TexCoord); 
    
	FragColor =  result;
}