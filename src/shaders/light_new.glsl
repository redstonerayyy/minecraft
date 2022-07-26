#version 330 core

in vec3 FragPos;
in vec2 TexCoord;
in vec3 Normal;

out vec4 FragColor;

struct DirLight {
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform DirLight dirLight;

struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
  
#define NR_POINT_LIGHTS 1
uniform PointLight pointLights[NR_POINT_LIGHTS];

struct Material {
    vec3 specular;
    float shininess;
}; 

uniform Material material;
uniform sampler2D tex_sampler;
uniform sampler2D tex_sampler_two;
uniform vec3 viewPos;

void main()
{
    FragColor = texture2D(tex_sampler, TexCoord);
}