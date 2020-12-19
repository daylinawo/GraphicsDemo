#include "Primitives.h"
#include "glad.h"
#include "Object.h"

Primitives* Primitives::Instance()
{
	static Primitives* primitivesObject = new Primitives();
	return primitivesObject;
}
//*******************************************************************
// create all buffer objects
//*******************************************************************
void Primitives::CreateObjects()
{
	CreateCube3D();
	CreateQuad3D();
	CreateLine3D();
	CreateQuad2D();
}
//*******************************************************************
// create 3d cube object
//*******************************************************************
void Primitives::CreateCube3D()
{
	GLfloat vertices[] =
	{
		//front face
		-1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f,

		//back face
		-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,

		//left face
		-1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,

		//right face
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f,

		//top face
		-1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f,
		 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f,

		 //bottom face
		 -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f,
		  1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f,
	};

	GLfloat colors[] =
	{
		// front face
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,

		//back face
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,

		//left face
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,

		//right face
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,

		//top face
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,

		//bottom face
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f
	};

	GLfloat UV[] =
	{
		//front face
		0.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 0.0f,

		//back face
		0.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 0.0f,

		//left face
		0.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 0.0f,

		//right face
		0.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 0.0f,

		//top face
		0.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 0.0f,

		//bottom face
		0.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 0.0f
	};

	GLfloat normals[] =
	{
		//front face
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

		//back face
		0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f,

		//left face
		-1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

		//right face
		1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

		//top face
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

		//bottom face
		0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f
	};

	GLuint indices[] =
	{
		0, 1, 3, 3, 1, 2,
		4, 5, 7, 7, 5, 6,
		8, 9, 11, 11, 9, 10,
		12, 13, 15, 15, 13, 14,
		16, 17, 19, 19, 17, 18,
		20, 21, 23, 23, 21, 22
	};

	m_cubeBuffer3D.CreateBuffers("CUBE_3D", 36, true);

	//binding ebo and vbo
	m_cubeBuffer3D.BindEBO();
	m_cubeBuffer3D.BindVBO(Buffer::VERTEX_VBO, "vertexIn", Buffer::XYZ, Buffer::FLOAT);
	m_cubeBuffer3D.BindVBO(Buffer::COLOR_VBO, "colorIn", Buffer::RGBA, Buffer::FLOAT);
	m_cubeBuffer3D.BindVBO(Buffer::TEXTURE_VBO, "textureIn", Buffer::UV, Buffer::FLOAT);
	m_cubeBuffer3D.BindVBO(Buffer::NORMAL_VBO, "normalIn", Buffer::NORMAL, Buffer::FLOAT);

	//filling ebo and vbo with data
	m_cubeBuffer3D.SetEBOData(indices, sizeof(indices), Buffer::STATIC);
	m_cubeBuffer3D.SetVBOData(Buffer::VERTEX_VBO, vertices, sizeof(vertices), Buffer::DYNAMIC);
	m_cubeBuffer3D.SetVBOData(Buffer::COLOR_VBO, colors, sizeof(colors), Buffer::DYNAMIC);
	m_cubeBuffer3D.SetVBOData(Buffer::TEXTURE_VBO, UV, sizeof(UV), Buffer::DYNAMIC);
	m_cubeBuffer3D.SetVBOData(Buffer::NORMAL_VBO, normals, sizeof(normals), Buffer::DYNAMIC);
}
//*******************************************************************
// create 3d quad object
//*******************************************************************
void Primitives::CreateQuad3D()
{
	GLfloat vertices[] =
	{
		-1.0f, 1.0f, 0.0f,
		 1.0f, 1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f
	};

	GLfloat colors[] =
	{
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f
	};

	GLfloat UV[] =
	{
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};

	GLfloat normals[] =
	{
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	GLuint indices[] = { 0, 1, 3, 3, 1, 2 };

	m_quadBuffer3D.CreateBuffers("QUAD_3D", 6, true);

	m_quadBuffer3D.BindEBO();
	m_quadBuffer3D.BindVBO(Buffer::VERTEX_VBO, "vertexIn", Buffer::XYZ, Buffer::DataType::FLOAT);
	m_quadBuffer3D.BindVBO(Buffer::COLOR_VBO, "colorIn", Buffer::RGBA, Buffer::DataType::FLOAT);
	m_quadBuffer3D.BindVBO(Buffer::TEXTURE_VBO, "textureIn", Buffer::UV, Buffer::DataType::FLOAT);
	m_quadBuffer3D.BindVBO(Buffer::NORMAL_VBO, "normalIn", Buffer::NORMAL, Buffer::DataType::FLOAT);

	m_quadBuffer3D.SetEBOData(indices, sizeof(indices), Buffer::DYNAMIC);
	m_quadBuffer3D.SetVBOData(Buffer::VERTEX_VBO, vertices, sizeof(vertices), Buffer::DYNAMIC);
	m_quadBuffer3D.SetVBOData(Buffer::COLOR_VBO, colors, sizeof(colors), Buffer::DYNAMIC);
	m_quadBuffer3D.SetVBOData(Buffer::TEXTURE_VBO, UV, sizeof(UV), Buffer::DYNAMIC);
	m_quadBuffer3D.SetVBOData(Buffer::NORMAL_VBO, normals, sizeof(normals), Buffer::DYNAMIC);
}
//*******************************************************************
// create 2d quad object
//*******************************************************************
void Primitives::CreateQuad2D()
{
	GLuint vertices[] =
	{
		0, 1, 0,
		1, 1, 0,
		1, 0, 0,
		0, 0, 0
	};

	GLfloat colors[] =
	{
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f
	};

	GLfloat UV[] =
	{
		0.0f, 0.0f, 
		1.0f, 0.0f,
		1.0f, 1.0f, 
		0.0f, 1.0f
	};

	GLfloat normals[] =
	{
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 
		0.0f, 1.0f, 0.0f
	};

	GLuint indices[] = { 0, 1, 3, 3, 1, 2 };

	m_quadBuffer2D.CreateBuffers("QUAD_2D", 6, true);

	m_quadBuffer2D.BindEBO();
	m_quadBuffer2D.BindVBO(Buffer::VERTEX_VBO, "vertexIn", Buffer::XYZ, Buffer::DataType::UINT);
	m_quadBuffer2D.BindVBO(Buffer::COLOR_VBO, "colorIn", Buffer::RGBA, Buffer::DataType::FLOAT);
	m_quadBuffer2D.BindVBO(Buffer::TEXTURE_VBO, "textureIn", Buffer::UV, Buffer::DataType::FLOAT);
	m_quadBuffer2D.BindVBO(Buffer::NORMAL_VBO, "normalIn", Buffer::NORMAL, Buffer::DataType::FLOAT);
	
	m_quadBuffer2D.SetEBOData(indices, sizeof(indices), Buffer::DYNAMIC);
	m_quadBuffer2D.SetVBOData(Buffer::VERTEX_VBO, vertices, sizeof(vertices), Buffer::DYNAMIC);
	m_quadBuffer2D.SetVBOData(Buffer::COLOR_VBO, colors, sizeof(colors), Buffer::DYNAMIC);
	m_quadBuffer2D.SetVBOData(Buffer::TEXTURE_VBO, UV, sizeof(UV), Buffer::DYNAMIC);
	m_quadBuffer2D.SetVBOData(Buffer::NORMAL_VBO, normals, sizeof(normals), Buffer::DYNAMIC);
}
//*******************************************************************
// create 3d line object
//*******************************************************************
void Primitives::CreateLine3D()
{
	m_lineBuffer3D.CreateBuffers("LINE_3D", 2, false);

	m_lineBuffer3D.BindVBO(Buffer::VERTEX_VBO, "vertexIn", Buffer::XYZ, Buffer::FLOAT);
	m_lineBuffer3D.BindVBO(Buffer::COLOR_VBO, "colorIn", Buffer::RGB, Buffer::FLOAT);
	m_lineBuffer3D.SetVBOData(Buffer::VERTEX_VBO, (GLfloat*) nullptr, 6 * sizeof(GLfloat), Buffer::DYNAMIC);
	m_lineBuffer3D.SetVBOData(Buffer::COLOR_VBO, (GLfloat*) nullptr, 6 * sizeof(GLfloat), Buffer::DYNAMIC);
}
//*******************************************************************
// draw 3d cube
//*******************************************************************
void Primitives::DrawCube3D(bool isLit, bool isTextured)
{
	Object::SendToShader(isLit, isTextured);

	m_cubeBuffer3D.Draw(Buffer::TRIANGLES);
}
//*******************************************************************
// draw 3d quad
//*******************************************************************
void Primitives::DrawQuad3D(bool isLit, bool isTextured)
{
	Object::SendToShader(isLit, isTextured);

	m_quadBuffer3D.Draw(Buffer::TRIANGLES);
}
//*******************************************************************
// draw 3d line
//*******************************************************************
void Primitives::DrawLine3D(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2,
							GLfloat z2, GLfloat lineWidth, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	GLfloat vertices[] = { x1, y1, z1, x2, y2, z2 };
	GLfloat colors[] = { r, g, b, a, r, g, b, a};

	m_lineBuffer3D.BindVBO(Buffer::VERTEX_VBO, "vertexIn", Buffer::XYZ, Buffer::FLOAT);
	m_lineBuffer3D.BindVBO(Buffer::COLOR_VBO, "colorIn", Buffer::RGBA, Buffer::FLOAT);
	m_lineBuffer3D.SetVBOData(Buffer::VERTEX_VBO, vertices, sizeof(vertices), Buffer::DYNAMIC);
	m_lineBuffer3D.SetVBOData(Buffer::COLOR_VBO, colors, sizeof(colors), Buffer::DYNAMIC);

	Object::SendToShader(false, false);

	m_lineBuffer3D.SetLineWidth(lineWidth);

	m_lineBuffer3D.Draw(Buffer::LINES);

	m_lineBuffer3D.SetLineWidth(1.0f);
}
//*******************************************************************
// draw 2d quad
//*******************************************************************
void Primitives::DrawQuad2D(bool isLit, bool isTextured)
{
	Object::SendToShader(isLit, isTextured);

	m_quadBuffer2D.Draw(Buffer::TRIANGLES);
}
//*******************************************************************
// destroy all buffer objects
//*******************************************************************
void Primitives::DestroyBuffers()
{
	m_cubeBuffer3D.DestroyBuffers();
	m_quadBuffer3D.DestroyBuffers();
	m_lineBuffer3D.DestroyBuffers();
	m_quadBuffer2D.DestroyBuffers();
}