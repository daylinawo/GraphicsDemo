#ifndef BUFFER_H
#define BUFFER_H

#include "glad.h"

#include <map>
#include <string>

struct BufferData
{
	bool hasEBO;

	GLuint vao;
	GLuint ebo;
	GLuint vbo[4];
	GLsizei totalVertices;
};

class Buffer
{
public:

	enum VBOType { VERTEX_VBO, COLOR_VBO, TEXTURE_VBO, NORMAL_VBO };
	enum DataType { FLOAT, UINT };
	enum FillMode { STATIC, DYNAMIC };
	enum RenderMode { POINTS, LINES, TRIANGLES };
	enum ComponentSize { XY, UV, XYZ, RGB, RGBA, NORMAL };

public:

	Buffer();
	~Buffer();

public:

	void CreateBuffers(const std::string& bufferID, GLsizei totalVertices, bool hasEBO);
	void DestroyBuffers();

public:

	void BindVBO(VBOType vboType, const std::string& vertAttrib, ComponentSize componentSize, DataType dataType);
	void BindEBO();

	bool SetBuffer(const std::string& bufferID);
	void SetVBOData(VBOType vboType, const void* data, GLsizeiptr size, FillMode fillMode);
	void SetEBOData(const void* data, GLsizeiptr size, FillMode fillMode);
	void AddVBOData(VBOType vboType, const void* data, GLsizeiptr size, GLuint offset);
	void Draw(RenderMode renderMode);

	void SetLineWidth(GLfloat width);

private:

	static std::map<std::string, BufferData>* s_bufferMap;

	BufferData m_data;
};

#endif