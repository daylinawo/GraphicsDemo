#version 460

#define DIRECTIONAL_LIGHT 1
#define POINT_LIGHT 2
#define TOTAL_LIGHTS 5

struct Light
{
	int type;
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float attenuationConst;
	float attenuationLinear;
	float attenuationQuad;

	bool isActive;
};

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

in vec3 vertexOut;
in vec4 colorOut;
in vec2 textureOut;
in vec3 normalOut;

out vec4 pixelColor;

uniform bool isLit;
uniform bool isSkybox;
uniform bool isTextured;

uniform Light lights[TOTAL_LIGHTS];
uniform Material material;
uniform vec3 cameraPosition;

uniform samplerCube skybox;
uniform sampler2D textureImage;

//****************************************
//calculate the ambient color
//****************************************
vec3 AmbientColor(Light light)
{
	return  light.ambient * material.ambient;
}

//****************************************
//calculate the diffuse color
//****************************************
vec3 DiffuseColor(Light light, vec3 normal)
{
	vec3 lightDirection;

	if(light.type == POINT_LIGHT)
	{
		lightDirection = normalize(light.position - vertexOut);
	}
	else
	{
		lightDirection = normalize(light.position);
	}

	float lightIntensity = max(dot(lightDirection, normal), 0.0f);

	return light.diffuse * material.diffuse * lightIntensity;
}

//****************************************
//calculate the specular color
//****************************************
vec3 SpecularColor(Light light, vec3 normal)
{
	vec3 lightDirection = normalize(light.position - vertexOut);
	vec3 viewDirection = normalize(cameraPosition - vertexOut);

	vec3 reflection = reflect(-lightDirection, normal);		
	float specularTerm = pow(max(dot(viewDirection, reflection), 0.0f), material.shininess);

	return light.specular * material.specular * specularTerm;
}

//****************************************
//calculate the attenuation
//****************************************
float Attenuation(Light light)
{
	float distanceToLight = length(light.position - vertexOut);

	return	1.0 / (light.attenuationConst + light.attenuationLinear * distanceToLight + 
			       light.attenuationQuad * (distanceToLight * distanceToLight));
}

void main(void)
{
	if(isLit)
	{
		vec3 normal = normalize(normalOut);

		for(int i = 0; i < TOTAL_LIGHTS; i++)
		{
			if(lights[i].isActive)
			{
				//calculate total fragment color
				vec3 totalColor = AmbientColor(lights[i]) +
								  DiffuseColor(lights[i], normal) +
								  SpecularColor(lights[i], normal);

				//make sure RGB components never go beyond 1.0
				totalColor.r = min(totalColor.r, 1.0f);
				totalColor.g = min(totalColor.g, 1.0f);
				totalColor.b = min(totalColor.b, 1.0f);
			
				if(lights[i].type == POINT_LIGHT)
				{
					if(length(totalColor) > 0)
						//add attenuation before appending to final colour value
						pixelColor += vec4(totalColor * Attenuation(lights[i]), colorOut.a);
				}
				else
				{
					pixelColor += vec4(totalColor, colorOut.a);
				}
			}
		}

		if(isTextured)
		{
			pixelColor *= texture(textureImage, textureOut); 
		}

	}
	else
	{
		if(isTextured)
		{
			pixelColor = colorOut * texture(textureImage, textureOut); 
		}
		else
		{
			pixelColor = colorOut;
		}
	}

}