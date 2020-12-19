#include "Grid.h"
#include "glad.h"
#include "Pipeline.h"
#include "glm.hpp"

const int AXES = 3;
const int SIZE = 15;
const int QUADRANTS = 4;
const int BYTES_PER_LINE = 6 * sizeof(GLfloat);
const int TOTAL_BYTES_VBO = SIZE * QUADRANTS * BYTES_PER_LINE;

Grid::Grid()
{
	m_model = glm::mat4(1.0f);
	m_position = glm::vec3(0.0f);
	m_colors = glm::vec3(1.0f, 1.0f, 1.0f);
}

void Grid::CreateGrid()
{
	GLuint offset = 0;

	//total vertices = grid size * total quadrants * 2 vertices
	m_gridBuffer.CreateBuffers("GRID", SIZE * QUADRANTS * 2, false);

	m_gridBuffer.BindVBO(Buffer::VERTEX_VBO, "vertexIn", Buffer::XYZ, Buffer::DataType::FLOAT);
	m_gridBuffer.BindVBO(Buffer::COLOR_VBO, "colorIn", Buffer::RGB, Buffer::DataType::FLOAT);

	//total size for vertex and color buffers
	int bufferSize = TOTAL_BYTES_VBO;
	int size = SIZE;

	m_gridBuffer.SetVBOData(Buffer::VERTEX_VBO, nullptr, bufferSize, Buffer::DYNAMIC);
	m_gridBuffer.SetVBOData(Buffer::COLOR_VBO, nullptr, bufferSize, Buffer::DYNAMIC);

	//*****************************************
	//create grid lines for negative x quadrant
	//*****************************************

	for (int i = 0; i < size; i++)
	{
		GLfloat vertices[] =
		{
			(GLfloat)(-size + i), 0.0f, (GLfloat)size,  //positive Z
			(GLfloat)(-size + i), 0.0f, (GLfloat)-size, //negative Z
		};

		GLfloat colors[] =
		{
			m_colors.r, m_colors.g, m_colors.b,
			m_colors.r, m_colors.g, m_colors.b
		};

		m_gridBuffer.AddVBOData(Buffer::VERTEX_VBO, vertices, sizeof(vertices), offset);
		m_gridBuffer.AddVBOData(Buffer::COLOR_VBO, colors, sizeof(colors), offset);

		offset += BYTES_PER_LINE;
	}

	//*****************************************
	//create grid lines for positive x quadrant
	//*****************************************

	for (int i = 0; i < size; i++)
	{
		GLfloat vertices[] =
		{
			1.0f + i, 0.0f, (GLfloat)size,  //positive Z
			1.0f + i, 0.0f, (GLfloat)-size, //negative Z
		};

		GLfloat colors[] =
		{
			m_colors.r, m_colors.g, m_colors.b,
			m_colors.r, m_colors.g, m_colors.b
		};

		m_gridBuffer.AddVBOData(Buffer::VERTEX_VBO, vertices, sizeof(vertices), offset);
		m_gridBuffer.AddVBOData(Buffer::COLOR_VBO, colors, sizeof(colors), offset);

		offset += BYTES_PER_LINE;
	}

	//*****************************************
	//create grid lines for negative z quadrant
	//*****************************************

	for (int i = 0; i < size; i++)
	{
		GLfloat vertices[] =
		{
			(GLfloat)size, 0.0f, (GLfloat)(-size + i),  //positive X
			(GLfloat)-size, 0.0f, (GLfloat)(-size + i), //negative X
		};

		GLfloat colors[] =
		{
			m_colors.r, m_colors.g, m_colors.b,
			m_colors.r, m_colors.g, m_colors.b
		};

		m_gridBuffer.AddVBOData(Buffer::VERTEX_VBO, vertices, sizeof(vertices), offset);
		m_gridBuffer.AddVBOData(Buffer::COLOR_VBO, colors, sizeof(colors), offset);

		offset += BYTES_PER_LINE;
	}

	//*****************************************
	//create grid lines for positive z quadrant
	//*****************************************

	for (int i = 0; i < size; i++)
	{
		GLfloat vertices[] =
		{
			(GLfloat)(size), 0.0f, 1.0f + i,  //positive X
			(GLfloat)(-size), 0.0f, 1.0f + i, //negative X
		};

		GLfloat colors[] =
		{
			m_colors.r, m_colors.g, m_colors.b,
			m_colors.r, m_colors.g, m_colors.b
		};

		m_gridBuffer.AddVBOData(Buffer::VERTEX_VBO, vertices, sizeof(vertices), offset);
		m_gridBuffer.AddVBOData(Buffer::COLOR_VBO, colors, sizeof(colors), offset);

		offset += BYTES_PER_LINE;
	}
}

void Grid::CreateAxes()
{
	int size = SIZE;

	GLfloat vertices[] =
	{
		//x axis
		0.0f, 0.0f, (GLfloat)size,
		0.0f, 0.0f, (GLfloat)-size,	
		
		//y axis
		0.0f, (GLfloat)size, 0.0f,
		0.0f, (GLfloat)-size, 0.0f,	
		
		//z axis
		(GLfloat)size, 0.0f, 0.0f,
		(GLfloat)-size, 0.0f, 0.0f
	};

	GLfloat colors[] =
	{
		//red x axis
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,		
		
		//green y axis
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,		
		
		//blue z axis
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
	};

	m_axesBuffer.CreateBuffers("AXES", AXES * 2, false);

	m_axesBuffer.BindVBO(Buffer::VERTEX_VBO, "vertexIn", Buffer::XYZ, Buffer::FLOAT);
	m_axesBuffer.BindVBO(Buffer::COLOR_VBO, "colorIn", Buffer::RGB, Buffer::FLOAT);

	m_axesBuffer.SetVBOData(Buffer::VERTEX_VBO, vertices, sizeof(vertices), Buffer::STATIC);
	m_axesBuffer.SetVBOData(Buffer::COLOR_VBO, colors, sizeof(colors), Buffer::STATIC);
}

void Grid::DrawGrid()
{
	Pipeline::Instance()->SendUniformData("model", m_model);
	Pipeline::Instance()->SendUniformData("isLit", false);
	Pipeline::Instance()->SendUniformData("isTextured", false);

	m_gridBuffer.Draw(Buffer::RenderMode::LINES);
}

void Grid::DrawAxes()
{
	Pipeline::Instance()->SendUniformData("model", m_model);
	Pipeline::Instance()->SendUniformData("isLit", false);
	Pipeline::Instance()->SendUniformData("isTextured", false);

	m_axesBuffer.Draw(Buffer::RenderMode::LINES);
}


Grid::~Grid()
{
}
