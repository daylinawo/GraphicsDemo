#include "Light.h"
#include "Pipeline.h"

GLuint Light::s_totalLights = 0;

Light::Light()
{
	m_lightID = -1;
	
	m_isDirty = false;
	m_isActive = true;

	m_color = glm::vec3(0.0f);
	m_ambient = glm::vec3(0.0f);
	m_diffuse = glm::vec3(0.0f);
	m_specular = glm::vec3(0.0f);

	m_attenuationConst = 0.0f;
	m_attenuationLinear = 0.0f;
	m_attenuationQuad = 0.0f;

	m_lightType = LightType::DIRECTIONAL;
}
bool& Light::IsActive()
{
	return m_isActive;
}
//*******************************************************************
// send data to shader
//*******************************************************************
void Light::SendToShader()
{
	Pipeline::Instance()->SendUniformData("isLit", false);
	Pipeline::Instance()->SendUniformData("isTextured", false);
	Pipeline::Instance()->SendUniformData("model", m_transform.GetMatrix());

	std::string lightID = std::to_string(m_lightID);

	Pipeline::Instance()->SendUniformData("lights[" + lightID + "].position", m_transform.GetPosition());
	Pipeline::Instance()->SendUniformData("lights[" + lightID + "].ambient", m_ambient);
	Pipeline::Instance()->SendUniformData("lights[" + lightID + "].diffuse", m_diffuse);
	Pipeline::Instance()->SendUniformData("lights[" + lightID + "].specular", m_specular);
	Pipeline::Instance()->SendUniformData("lights[" + lightID + "].attenuationConst", m_attenuationConst);
	Pipeline::Instance()->SendUniformData("lights[" + lightID + "].attenuationLinear", m_attenuationLinear);
	Pipeline::Instance()->SendUniformData("lights[" + lightID + "].attenuationQuad", m_attenuationQuad);
	Pipeline::Instance()->SendUniformData("lights[" + lightID + "].type", m_lightType);
	Pipeline::Instance()->SendUniformData("lights[" + lightID + "].isActive", m_isActive);

}
//*******************************************************************
// set ambient color with vec3
//*******************************************************************
void Light::SetAmbient(const glm::vec3& ambient)
{
	m_ambient = ambient;
	m_isDirty = true;
}

//*******************************************************************
// set diffuse color with vec3
//*******************************************************************
void Light::SetDiffuse(const glm::vec3& diffuse)
{
	m_diffuse = diffuse;
}

//*******************************************************************
// set specular color with vec3
//*******************************************************************
void Light::SetSpecular(const glm::vec3& specular)
{
	m_specular = specular;
}

//*******************************************************************
// set ambient color with floats
//*******************************************************************
void Light::SetAmbient(float r, float g, float b)
{
	m_ambient.r = r;
	m_ambient.g = g;
	m_ambient.b = b;
	m_isDirty = true;
}

//*******************************************************************
// set diffuse color with floats
//*******************************************************************
void Light::SetDiffuse(float r, float g, float b)
{
	m_diffuse.r = r;
	m_diffuse.g = g;
	m_diffuse.b = b;
}

//*******************************************************************
// set specular color with floats
//*******************************************************************
void Light::SetSpecular(float r, float g, float b)
{
	m_specular.r = r;
	m_specular.g = g;
	m_specular.b = b;
}

//*******************************************************************
// set attenuation values
//*******************************************************************
void Light::SetAttenuation(float attenuationConst, float attenuationLinear, float attenuationQuad)
{
	m_attenuationConst = attenuationConst;
	m_attenuationLinear = attenuationLinear;
	m_attenuationQuad = attenuationQuad;
}
//*******************************************************************
// set object position
//*******************************************************************
void Light::SetPosition(float x, float y, float z)
{
	m_transform.SetPosition(x, y, z);
}

