#include "Buffer.h"
#include "Pipeline.h"

Buffer::Buffer()
{
	m_VAO = -1;
	m_EBO = -1;
	m_index = -1;
	m_colorVBO = -1;
	m_vertexVBO = -1;
	m_totalVertices = 0;

	m_hasEBO = false;
}

void Buffer::CreateBuffers(GLsizei totalVertices, bool hasEBO)
{
	m_totalVertices = totalVertices;
	m_hasEBO = hasEBO;

	//generate new name for new VAOs, VBOs, and EBOs
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_vertexVBO);
	glGenBuffers(1, &m_colorVBO);

	if (hasEBO) { glGenBuffers(1, &m_EBO); }
}

void Buffer::BindVBO(VBOType vboType, const std::string& vertAttrib, ComponentType componentType, DataType dataType, bool isNormalized)
{
	GLint size = 0;
	GLuint vboID = -1;
	GLboolean normalized = (isNormalized) ? GL_FALSE : GL_TRUE;
	GLenum type = (dataType == DataType::FLOAT) ? GL_FLOAT : GL_UNSIGNED_INT;
	
	switch (vboType)
	{
		case VBOType::VERTEX: { vboID = m_vertexVBO; break; }
		case VBOType::COLOR:  { vboID = m_colorVBO; break;  }
	}	

	switch (componentType)
	{
		case ComponentType::XY:  { size = 2; break; }
		case ComponentType::XYZ: { size = 3; break; }
		case ComponentType::RGB: { size = 3; break; }
	}

	glBindVertexArray(m_VAO);

		//bind VBO and define data structure
		glBindBuffer(GL_ARRAY_BUFFER, vboID);

		Pipeline::Instance()->BindAttribute(vertAttrib);
		glVertexAttribPointer(Pipeline::Instance()->GetAttributeID(vertAttrib), size, type, normalized, 0, 0);
		glEnableVertexAttribArray(Pipeline::Instance()->GetAttributeID(vertAttrib));

	glBindVertexArray(0);
}

void Buffer::BindEBO()
{
	glBindVertexArray(m_VAO);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

	glBindVertexArray(0);
}

void Buffer::SetVBOData(VBOType vboType, const void* data, GLsizeiptr size, DataMode dataMode)
{
	GLuint vboID = -1;
	GLenum mode = (dataMode == DataMode::STATIC) ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;

	switch (vboType)
	{
		case VBOType::VERTEX: { vboID = m_vertexVBO; break; }
		case VBOType::COLOR:  { vboID = m_colorVBO; break;  }
	}

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, size, data, mode);
}

void Buffer::SetEBOData(const void* data, GLsizeiptr size, DataMode dataMode)
{
	GLenum mode = (dataMode == DataMode::STATIC) ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, mode);
}

void Buffer::Draw(RenderMode renderMode)
{
	GLenum mode = -1;

	switch (renderMode)
	{
		case RenderMode::POINTS:	{ mode = GL_POINTS; break;    }
		case RenderMode::LINES:	    { mode = GL_LINES; break;     }
		case RenderMode::TRIANGLES: { mode = GL_TRIANGLES; break; }
	}

	glBindVertexArray(m_VAO);

	(m_hasEBO) ? glDrawElements(mode, m_totalVertices, GL_UNSIGNED_INT, 0) :
				 glDrawArrays(mode, 0, m_totalVertices);

	glBindVertexArray(0);
}


Buffer::~Buffer()
{
	glDeleteBuffers(1, &m_vertexVBO);
	glDeleteBuffers(1, &m_colorVBO);
	glDeleteBuffers(1, &m_EBO);
	glDeleteBuffers(1, &m_VAO);
}

