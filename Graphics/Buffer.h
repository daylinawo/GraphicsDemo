#pragma once

#include "glad.h"
#include <string>

class Buffer
{

public:

	enum class VBOType { VERTEX, COLOR };
	enum class DataType { FLOAT, UINT };
	enum class DataMode { STATIC, DYNAMIC };
	enum class RenderMode { POINTS, LINES, TRIANGLES};
	enum class ComponentType { XY, XYZ, RGB };

public:

	Buffer();
	~Buffer();

public:

	void CreateBuffers(GLsizei totalVertices, bool hasEBO);
	
public:

	void BindVBO(VBOType vboType, const std::string& vertAttrib, ComponentType componentType, DataType dataType, bool isNormalized);
	void BindEBO();

	void SetVBOData(VBOType vboType, const void* data, GLsizeiptr size, DataMode dataMode);
	void SetEBOData(const void* data, GLsizeiptr size, DataMode dataMode);

	void Draw(RenderMode renderMode);

private:

	bool m_hasEBO;

	GLsizei m_totalVertices;

	GLuint m_vertexVBO;
	GLuint m_colorVBO;
	GLuint m_EBO;
	GLuint m_VAO;
	GLuint m_index;

};

