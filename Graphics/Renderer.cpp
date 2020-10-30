#include "Renderer.h"
#include "Screen.h"
#include "Input.h"
#include "Pipeline.h"

Renderer::Renderer()
{
	m_time = 0.0f;

	GLfloat vertices[] = { -0.5f, 0.5f,
						    0.5f, 0.5f,
						   0.5f, -0.5f,
						   -0.5f, -0.5f};

	GLfloat colors[] = { 1.0f, 0.0f, 0.0f,
					     0.0f, 0.0f, 1.0f,
					     0.0f, 1.0f, 1.0f,
					     0.0f, 1.0f, 1.0f };

	GLuint indices[] = { 0, 1, 3, 3, 1 , 2 };

	Pipeline::Instance()->BindAttribute("vertexIn");
	Pipeline::Instance()->BindAttribute("colorIn");
	Pipeline::Instance()->BindUniform("time");

	GLint attributeIDVert = Pipeline::Instance()->GetAttributeID("vertexIn");
	GLint attributeIDColor = Pipeline::Instance()->GetAttributeID("colorIn");


	m_VAO = 0;
	m_EBO = 0;
	m_vertexVBO = 0;
	m_colorVBO = 0;

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_vertexVBO);
	glGenBuffers(1, &m_colorVBO);
	glGenBuffers(1, &m_EBO);

	glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(attributeIDVert, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(attributeIDVert);

		glBindBuffer(GL_ARRAY_BUFFER, m_colorVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
		glVertexAttribPointer(attributeIDColor, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(attributeIDColor);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void Renderer::Draw()
{
	//clear the frame buffer
	Screen::Instance()->ClearBuffer();

	glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	Screen::Instance()->SwapBuffer();
}

void Renderer::Update()
{
	m_time += 0.001f;
	Pipeline::Instance()->SendUniformData("time", m_time);
}

Renderer::~Renderer()
{

	glDeleteBuffers(1, &m_EBO);
	glDeleteBuffers(1, &m_colorVBO);
	glDeleteBuffers(1, &m_vertexVBO);
	glDeleteVertexArrays(1, &m_VAO);

}