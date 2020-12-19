#include "PointLight.h"
#include "Input.h"
#include "Object.h"

const float MOVE_SPEED = 10.0f;

PointLight::PointLight()
{
	m_isDirty = false;
	m_lightType = LightType::POINT;
}
//*******************************************************************
// create default light object
//*******************************************************************
void PointLight::Create()
{
	m_lightID = s_totalLights++;

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

	m_buffer.CreateBuffers("LIGHT", 6, true);

	m_buffer.BindEBO();
	m_buffer.BindVBO(Buffer::VERTEX_VBO, "vertexIn", Buffer::XYZ, Buffer::FLOAT);
	m_buffer.BindVBO(Buffer::COLOR_VBO, "colorIn", Buffer::RGB, Buffer::FLOAT);

	m_buffer.SetEBOData(indices, sizeof(indices), Buffer::STATIC);
	m_buffer.SetVBOData(Buffer::VERTEX_VBO, vertices, sizeof(vertices), Buffer::STATIC);
	m_buffer.SetVBOData(Buffer::COLOR_VBO, colors, sizeof(colors), Buffer::STATIC);

	m_transform.SetScale(0.25f, 0.25f, 0.0f);
}

void PointLight::Update(float deltaTime)
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

		m_buffer.SetVBOData(Buffer::COLOR_VBO, colors, sizeof(colors), Buffer::STATIC);

		m_isDirty = false;
	}
}
//*******************************************************************
// draw light object
//*******************************************************************
void PointLight::Draw()
{
	Object::SetMatrix(m_transform.GetMatrix());

	SendToShader();

	m_buffer.Draw(Buffer::RenderMode::TRIANGLES);
}

//*******************************************************************
// destroy object
//*******************************************************************
void PointLight::Destroy()
{
	m_buffer.DestroyBuffers();
	s_totalLights--;
}