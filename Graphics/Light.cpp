#include "Light.h"
#include "Input.h"
#include "Pipeline.h"

const float INTENSITY_RATE = 1.5f;
const float MOVE_SPEED = 10.0f;

Light::Light()
{
	m_isDirty = false;

	m_color = glm::vec3(0.0f);
	m_ambient = glm::vec3(0.0f);
	m_diffuse = glm::vec3(0.0f);
	m_specular = glm::vec3(0.0f);

	m_attenuationConst = 0.0f;
	m_attenuationLinear = 0.0f;
	m_attenuationQuad = 0.0f;

	static bool isBound = false;

	if (!isBound)
	{
		Pipeline::Instance()->BindUniform("isLit");
		Pipeline::Instance()->BindUniform("light.position");
		Pipeline::Instance()->BindUniform("light.ambient");
		Pipeline::Instance()->BindUniform("light.diffuse");
		Pipeline::Instance()->BindUniform("light.specular");
		Pipeline::Instance()->BindUniform("light.attenuationConst");
		Pipeline::Instance()->BindUniform("light.attenuationLinear");
		Pipeline::Instance()->BindUniform("light.attenuationQuad");

		isBound = true;
	}
}

//*******************************************************************
// create default light object
//*******************************************************************
void Light::Create()
{
	m_ambient = glm::vec3(1.0f);
	m_diffuse = glm::vec3(1.0f);
	m_specular = glm::vec3(1.0f);

	m_attenuationConst = 1.0f;
	m_attenuationLinear = 0.0f;
	m_attenuationQuad = 0.0f;

	//create a visual representation of light source
	GLfloat vertices[] = 
	{ 
		-1.0f, 1.0f, 0.0f,
		 1.0f, 1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f
	};

	GLfloat colors[] = 
	{ 
		m_ambient.r, m_ambient.g, m_ambient.b,
		m_ambient.r, m_ambient.g, m_ambient.b,
		m_ambient.r, m_ambient.g, m_ambient.b,
		m_ambient.r, m_ambient.g, m_ambient.b
	};

	GLuint indices[] = { 0, 1, 3, 3, 1, 2 };

	m_buffer.CreateBuffers(6, true);
	
	m_buffer.BindEBO();
	m_buffer.BindVBO(Buffer::VBOType::VERTEX, "vertexIn", Buffer::ComponentType::XYZ, Buffer::DataType::FLOAT);
	m_buffer.BindVBO(Buffer::VBOType::COLOR, "colorIn", Buffer::ComponentType::RGB, Buffer::DataType::FLOAT);

	m_buffer.SetEBOData(indices, sizeof(indices), Buffer::DataMode::STATIC);
	m_buffer.SetVBOData(Buffer::VBOType::VERTEX, vertices, sizeof(vertices), Buffer::DataMode::STATIC);
	m_buffer.SetVBOData(Buffer::VBOType::COLOR, colors, sizeof(colors), Buffer::DataMode::STATIC);

	m_transform.Translate(0.0f, 7.0f, 1.0f);
	m_transform.SetScale(0.25f, 0.25f, 0.0f);
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
// update light object logic
//*******************************************************************
void Light::Update(float deltaTime)
{
	float moveBy = MOVE_SPEED * deltaTime;

	if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_W))
	{
		m_transform.Translate(0.0f, 0.0f, -moveBy);
	}
	else if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_A))
	{
		m_transform.Translate(-moveBy, 0.0f, 0.0f);
	}
	else if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_S))
	{
		m_transform.Translate(0.0f, 0.0f, moveBy);
	}
	else if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_D))
	{
		m_transform.Translate(moveBy, 0.0f, 0.0f);
	}

	if (m_isDirty)
	{
		GLfloat colors[] =
		{
			m_ambient.r, m_ambient.g, m_ambient.b,
			m_ambient.r, m_ambient.g, m_ambient.b,
			m_ambient.r, m_ambient.g, m_ambient.b,
			m_ambient.r, m_ambient.g, m_ambient.b
		};

		m_buffer.SetVBOData(Buffer::VBOType::COLOR, colors, sizeof(colors), Buffer::DataMode::STATIC);

		m_isDirty = false;
	}
}

//*******************************************************************
// draw light object
//*******************************************************************
void Light::Draw()
{
	SendToShader();

	m_buffer.Draw(Buffer::RenderMode::TRIANGLES);
}

//*******************************************************************
// send data to shader
//*******************************************************************
void Light::SendToShader()
{

	Pipeline::Instance()->SendUniformData("isLit", false);
	Pipeline::Instance()->SendUniformData("isTextured", false);
	Pipeline::Instance()->SendUniformData("model", m_transform.GetMatrix());

	Pipeline::Instance()->SendUniformData("light.position", m_transform.GetPosition());
	Pipeline::Instance()->SendUniformData("light.ambient", m_ambient);
	Pipeline::Instance()->SendUniformData("light.diffuse", m_diffuse);
	Pipeline::Instance()->SendUniformData("light.specular", m_specular);
	Pipeline::Instance()->SendUniformData("light.attenuationConst", m_attenuationConst);
	Pipeline::Instance()->SendUniformData("light.attenuationLinear", m_attenuationLinear);
	Pipeline::Instance()->SendUniformData("light.attenuationQuad", m_attenuationQuad);

}

//*******************************************************************
// destroy object
//*******************************************************************
void Light::Destroy()
{
	m_buffer.DestroyBuffers();
}
