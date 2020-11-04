#include "Input.h"
#include "Pipeline.h"
#include "Renderer.h"
#include "Screen.h"

#include <gtc\matrix_transform.hpp>

const float SPEED = 4.0f;

Renderer::Renderer()
{
	m_time = 0.0f;

	m_model = glm::mat4(1.0f);
	m_scale = glm::vec3(0.25f);
	m_position = glm::vec3(0.0f);
	m_dimensions = glm::vec3(0.5f);

	m_camera = new Camera();

	GLfloat vertices[] =
	{
		//front face
		m_position.x - m_dimensions.x, m_position.y + m_dimensions.y, m_dimensions.z,
		m_position.x + m_dimensions.x, m_position.y + m_dimensions.y, m_dimensions.z,
		m_position.x + m_dimensions.x, m_position.y - m_dimensions.y, m_dimensions.z,
		m_position.x - m_dimensions.x, m_position.y - m_dimensions.y, m_dimensions.z,

		//back face
		m_position.x - m_dimensions.x, m_position.y + m_dimensions.y, -m_dimensions.z,
		m_position.x + m_dimensions.x, m_position.y + m_dimensions.y, -m_dimensions.z,
		m_position.x + m_dimensions.x, m_position.y - m_dimensions.y, -m_dimensions.z,
		m_position.x - m_dimensions.x, m_position.y - m_dimensions.y, -m_dimensions.z,

		//left face
		m_position.x - m_dimensions.x, m_position.y + m_dimensions.y, m_dimensions.z,
		m_position.x - m_dimensions.x, m_position.y + m_dimensions.y, -m_dimensions.z,
		m_position.x - m_dimensions.x, m_position.y - m_dimensions.y, -m_dimensions.z,
		m_position.x - m_dimensions.x, m_position.y - m_dimensions.y, m_dimensions.z,

		//right face
		m_position.x + m_dimensions.x, m_position.y + m_dimensions.y, m_dimensions.z,
		m_position.x + m_dimensions.x, m_position.y + m_dimensions.y, -m_dimensions.z,
		m_position.x + m_dimensions.x, m_position.y - m_dimensions.y, -m_dimensions.z,
		m_position.x + m_dimensions.x, m_position.y - m_dimensions.y, m_dimensions.z,

		//top face
		m_position.x - m_dimensions.x, m_position.y + m_dimensions.y, m_dimensions.z,
		m_position.x - m_dimensions.x, m_position.y + m_dimensions.y, -m_dimensions.z,
		m_position.x + m_dimensions.x, m_position.y + m_dimensions.y, -m_dimensions.z,
		m_position.x + m_dimensions.x, m_position.y + m_dimensions.y, m_dimensions.z,

		//bottom face
		m_position.x - m_dimensions.x, m_position.y - m_dimensions.y, m_dimensions.z,
		m_position.x - m_dimensions.x, m_position.y - m_dimensions.y, -m_dimensions.z,
		m_position.x + m_dimensions.x, m_position.y - m_dimensions.y, -m_dimensions.z,
		m_position.x + m_dimensions.x, m_position.y - m_dimensions.y, m_dimensions.z,
	};

	GLfloat colors[] =
	{ 
		//red front face
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		//green back face
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		//blue left face
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,

		//cyan right face
		0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f,

		//yellow top face
		1.0f, 1.0f, 0.0f, 
		1.0f, 1.0f, 0.0f, 
		1.0f, 1.0f, 0.0f, 
		1.0f, 1.0f, 0.0f, 

		//purple bottom face
		1.0f, 0.0f, 1.0f, 
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f
	};

	GLuint indices[] = { 0, 1, 3, 3, 1, 2,
						 4, 5, 7, 7, 5, 6,
						 8, 9, 11, 11, 9, 10,
						 12, 13, 15, 15, 13, 14,
						 16, 17, 19, 19, 17, 18,
						 20, 21, 23, 23, 21, 22 };

	glEnable(GL_DEPTH_TEST);

	m_buffer.CreateBuffers(36, true);

	m_buffer.BindEBO();
	m_buffer.BindVBO(Buffer::VBOType::VERTEX, "vertexIn", Buffer::ComponentType::XYZ, Buffer::DataType::FLOAT, false);
	m_buffer.BindVBO(Buffer::VBOType::COLOR, "colorIn", Buffer::ComponentType::RGB, Buffer::DataType::FLOAT, false);	
	
	m_buffer.SetEBOData(indices, sizeof(indices), Buffer::DataMode::STATIC);
	m_buffer.SetVBOData(Buffer::VBOType::VERTEX, vertices, sizeof(vertices), Buffer::DataMode::STATIC);
	m_buffer.SetVBOData(Buffer::VBOType::COLOR, colors, sizeof(colors), Buffer::DataMode::STATIC);

	//bind attributes and uniforms in shader so we can access them
	Pipeline::Instance()->BindUniform("time");
	Pipeline::Instance()->BindUniform("model");

	//get attribute ID of vertex and color attribute
	m_uniformIDModel = Pipeline::Instance()->GetUniformID("model");


	glUniformMatrix4fv(m_uniformIDModel, 1, GL_FALSE, &m_model[0][0]);
}

void Renderer::Update(float deltaTime)
{
	static bool isKeyPressed = false;

	if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_O) && !isKeyPressed)
	{
		if (Screen::Instance()->IsOutlineMode())
		{
			Screen::Instance()->SetOutlineMode(false);
		}
		else
		{
			Screen::Instance()->SetOutlineMode(true);
		}
	}

	if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_W))
	{
		m_position.y += SPEED * deltaTime;
	}
	else if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_A))
	{
		m_position.x -= SPEED * deltaTime;
	}
	else if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_S))
	{
		m_position.y -= SPEED * deltaTime;
	}
	else if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_D))
	{
		m_position.x += SPEED * deltaTime;
	}

	//translate on x and y axis
	m_model = glm::translate(glm::mat4(1.0f), m_position);

	//scale on x and y axis
	m_model = glm::scale(m_model, m_scale);

	glUniformMatrix4fv(m_uniformIDModel, 1, GL_FALSE, &m_model[0][0]);

	isKeyPressed = Input::Instance()->IsKeyPressed(SDL_SCANCODE_O);
	
	//m_time += 0.001f;
	//Pipeline::Instance()->SendUniformData("time", m_time);

	m_camera->Update(deltaTime);
}

void Renderer::Draw()
{
	//clear the frame buffer
	Screen::Instance()->ClearBuffer();

	m_buffer.Draw(Buffer::RenderMode::TRIANGLES);

	Screen::Instance()->SwapBuffer();
}

Renderer::~Renderer()
{
	delete m_camera;
	m_camera = nullptr;
}