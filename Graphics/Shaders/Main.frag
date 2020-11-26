#version 460

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float attenuationConst;
	float attenuationLinear;
	float attenuationQuad;
};

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

in vec3 vertexOut;
in vec3 colorOut;
in vec2 textureOut;
in vec3 normalOut;

out vec4 pixelColor;

uniform bool isLit;
uniform Light light;
uniform Material material;
uniform vec3 cameraPosition;

uniform bool isTextured;
uniform sampler2D textureImage;

vec3 normal = normalize(normalOut);
vec3 lightDirection = normalize(light.position - vertexOut);

//****************************************
//calculate the ambient color
//****************************************
vec3 CalculateAmbient()
{
	return  light.ambient * material.ambient;
}

//****************************************
//calculate the diffuse color
//****************************************
vec3 CalculateDiffuse()
{
	float lightIntensity = max(dot(lightDirection, normal), 0.0f);

	return light.diffuse * material.diffuse * lightIntensity;
}

//****************************************
//calculate the specular color
//****************************************
vec3 CalculateSpecular()
{
	vec3 viewDirection = normalize(cameraPosition - vertexOut);
	vec3 reflection = reflect(-lightDirection, normal);		
	float specularTerm = pow(max(dot(viewDirection, reflection), 0.0f), material.shininess);

	return light.specular * material.specular * specularTerm;
}

//****************************************
//calculate the attenuation
//****************************************
float CalculateAttenuation()
{
	float distanceToLight = length(light.position - vertexOut);

	return	1.0 / (light.attenuationConst + light.attenuationLinear * distanceToLight + 
			       light.attenuationQuad * (distanceToLight * distanceToLight));
}

void main(void)
{
	if(isLit)
	{
		vec3 ambient = CalculateAmbient();
		vec3 diffuse = CalculateDiffuse();
		vec3 specular = CalculateSpecular();
		float attenuation = CalculateAttenuation();

		if(isTextured)
		{
			pixelColor = attenuation *
						 vec4((ambient + diffuse + specular), 1.0) *
						 texture(textureImage, textureOut); 
		}
		else
		{
			pixelColor = attenuation * vec4((ambient + diffuse + specular), 1.0f);
		}
	}
	else
	{
		if(isTextured)
		{
			pixelColor = vec4(colorOut, 1.0f) * texture(textureImage, textureOut); 
		}
		else
		{
			pixelColor = vec4(colorOut, 1.0f); 
		}
	}

}