#include "Buffer.h"
#include "Pipeline.h"
#include "Utility.h"

std::map<std::string, BufferData>* Buffer::s_bufferMap = new std::map<std::string, BufferData>;

//*******************************************************************
// default constructor
//*******************************************************************
Buffer::Buffer()
{
	m_data.hasEBO = false;
	m_data.vao = 0;
	m_data.ebo = 0;
	m_data.vbo[VERTEX_VBO]= 0;
	m_data.vbo[COLOR_VBO]= 0;
	m_data.vbo[TEXTURE_VBO]= 0;
	m_data.vbo[NORMAL_VBO]= 0;
	m_data.totalVertices = 0;
}
//*******************************************************************
// create vao, ebo and vbos
//*******************************************************************
void Buffer::CreateBuffers(const std::string& bufferID, GLsizei totalVertices, bool hasEBO)
{
	m_data.totalVertices = totalVertices;
	m_data.hasEBO = hasEBO;

	glGenVertexArrays(1, &m_data.vao);
	glGenBuffers(1, &m_data.vbo[VERTEX_VBO]);
	glGenBuffers(1, &m_data.vbo[COLOR_VBO]);
	glGenBuffers(1, &m_data.vbo[TEXTURE_VBO]);
	glGenBuffers(1, &m_data.vbo[NORMAL_VBO]);

	if (hasEBO) { glGenBuffers(1, &m_data.ebo); }

	s_bufferMap->insert(std::pair<std::string, BufferData>(bufferID, m_data));
}
//*******************************************************************
// bind vertex buffer objects
//*******************************************************************
void Buffer::BindVBO(VBOType vboType, const std::string& vertAttrib, ComponentSize componentSize, DataType dataType)
{
	//current VBO ID
	GLuint vboID = -1;

	//number of components per vertex attribute
	GLint size = 0;

	//m_data.data type of each component in the array 
	GLenum _dataType = (dataType == DataType::FLOAT) ? GL_FLOAT : GL_UNSIGNED_INT;
	
	//select the correct vertex buffer object
	switch (vboType)
	{
		case VBOType::VERTEX_VBO:  { vboID = m_data.vbo[VERTEX_VBO]; break;  }
		case VBOType::COLOR_VBO:   { vboID = m_data.vbo[COLOR_VBO]; break;   }
		case VBOType::TEXTURE_VBO: { vboID = m_data.vbo[TEXTURE_VBO]; break; }
		case VBOType::NORMAL_VBO:  { vboID = m_data.vbo[NORMAL_VBO]; break;  }
	}	

	//define number of components per vertex attribute 
	switch (componentSize)
	{
		case ComponentSize::XY:  { size = 2; break; }
		case ComponentSize::UV:  { size = 2; break; }
		case ComponentSize::XYZ: { size = 3; break; }
		case ComponentSize::RGB: { size = 3; break; }
		case ComponentSize::RGBA: { size = 4; break; }
		case ComponentSize::NORMAL: { size = 3; break; }
	}

	glBindVertexArray(m_data.vao);

		//bind VBO and define m_data.data structure
		glBindBuffer(GL_ARRAY_BUFFER, vboID);

		Pipeline::Instance()->BindAttribute(vertAttrib);
		glVertexAttribPointer(Pipeline::Instance()->GetAttributeID(vertAttrib), size, _dataType, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(Pipeline::Instance()->GetAttributeID(vertAttrib));

	glBindVertexArray(0);
}
//*******************************************************************
// bind element buffer object
//*******************************************************************
void Buffer::BindEBO()
{
	glBindVertexArray(m_data.vao);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_data.ebo);

	glBindVertexArray(0);
}
//*******************************************************************
// set buffer data to specified pre-exisiting buffer data
//*******************************************************************
bool Buffer::SetBuffer(const std::string& bufferID)
{
	auto it = s_bufferMap->find(bufferID);

	if (it != s_bufferMap->end())
	{
		m_data = it->second;
		return true;
	}
	else
	{
		Utility::Log("Could not set texture ID: " + bufferID);
		return false;
	}
}
//*******************************************************************
// set vertex buffer data
//*******************************************************************
void Buffer::SetVBOData(VBOType vboType, const void* data, GLsizeiptr size, FillMode fillMode)
{
	GLuint vboID = -1;
	GLenum _fillMode = (fillMode == FillMode::STATIC) ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;

	//set type of buffer so we can fill the correct member VBO with m_data.data
	switch (vboType)
	{
		case VBOType::VERTEX_VBO:   { vboID = m_data.vbo[VERTEX_VBO]; break;  }
		case VBOType::COLOR_VBO:    { vboID = m_data.vbo[COLOR_VBO]; break;   }
		case VBOType::TEXTURE_VBO:  { vboID = m_data.vbo[TEXTURE_VBO]; break; }
		case VBOType::NORMAL_VBO:   { vboID = m_data.vbo[NORMAL_VBO]; break;  }

	}

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, size, data, _fillMode);
}
//*******************************************************************
// set element buffer data
//*******************************************************************
void Buffer::SetEBOData(const void* data, GLsizeiptr size, FillMode fillMode)
{
	GLenum _fillMode = (fillMode == FillMode::STATIC) ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_data.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, _fillMode);
}
//*******************************************************************
// append to vertex buffer data
//*******************************************************************
void Buffer::AddVBOData(VBOType vboType, const void* data, GLsizeiptr size, GLuint offset)
{
	GLuint vboID = -1;

	//set type of buffer so we can fill the correct member VBO with m_data.data
	switch (vboType)
	{
		case VBOType::VERTEX_VBO: { vboID = m_data.vbo[VERTEX_VBO]; break; }
		case VBOType::COLOR_VBO: { vboID = m_data.vbo[COLOR_VBO]; break;  }
	}

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}
//*******************************************************************
// draw object
//*******************************************************************
void Buffer::Draw(RenderMode renderMode)
{
	GLenum _renderMode = -1;

	switch (renderMode)
	{
		case RenderMode::POINTS:	{ _renderMode = GL_POINTS; break;    }
		case RenderMode::LINES:	    { _renderMode = GL_LINES; break;     }
		case RenderMode::TRIANGLES: { _renderMode = GL_TRIANGLES; break; }
	}

	glBindVertexArray(m_data.vao);

	(m_data.hasEBO) ? glDrawElements(_renderMode, m_data.totalVertices, GL_UNSIGNED_INT, 0) :
					  glDrawArrays(_renderMode, 0, m_data.totalVertices);

	glBindVertexArray(0);
}
//*******************************************************************
// set line width
//*******************************************************************
void Buffer::SetLineWidth(GLfloat width)
{
	glBindVertexArray(m_data.vao);

		glLineWidth(width);

	glBindVertexArray(0);
}
//*******************************************************************
// destroy vao, ebo and vbos
//*******************************************************************
void Buffer::DestroyBuffers()
{
	glDeleteBuffers(1, &m_data.vbo[VERTEX_VBO]);
	glDeleteBuffers(1, &m_data.vbo[COLOR_VBO]);
	glDeleteBuffers(1, &m_data.vbo[TEXTURE_VBO]);
	glDeleteBuffers(1, &m_data.vbo[NORMAL_VBO]);
	glDeleteBuffers(1, &m_data.vao);

	if (m_data.hasEBO) { glDeleteBuffers(1, &m_data.ebo); }
}

Buffer::~Buffer()
{
	DestroyBuffers();
}

