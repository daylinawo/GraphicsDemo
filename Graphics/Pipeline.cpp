#include "Pipeline.h"
#include <fstream>
#include <iostream>

Pipeline* Pipeline::Instance()
{
	static Pipeline* pipelineObject = new Pipeline();
	return pipelineObject;
}

Pipeline::Pipeline()
{
	m_shaderProgramID = 0;
	m_vertexShaderID = 0;
	m_fragmentShaderID = 0;
}

bool Pipeline::CreateProgram()
{
	m_shaderProgramID = glCreateProgram();

	if (!m_shaderProgramID)
	{
		std::cout << "Error creating shader program." << std::endl;
		system("pause");
		return false;
	}

	return true;
}

bool Pipeline::CreateShaders()
{
	m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

	if (!m_vertexShaderID)
	{
		std::cout << "Error creating vertex shader object." << std::endl;
		system("pause");
		return false;
	}

	m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	if (!m_vertexShaderID)
	{
		std::cout << "Error creating fragment shader object." << std::endl;
		system("pause");
		return false;
	}

	return true;
}

bool Pipeline::CompileShaders(const std::string& filename)
{
	std::fstream file(filename);

	if (!file)
	{
		std::cout << "Error reading shader file." << std::endl;
		system("pause");
		return false;
	}

	std::string line;
	std::string sourceCode;

	while (!file.eof())
	{
		std::getline(file, line);
		sourceCode += line + "\n";
	}

	file.close();

	//convert source code string to c-string
	const GLchar* sourceCodeC = static_cast<const GLchar*>(sourceCode.c_str());

	//bind source code to vertex shader object
	glShaderSource(m_vertexShaderID, 1, &sourceCodeC, nullptr);

	//compile vertex shader code
	glCompileShader(m_vertexShaderID);

	//================================================================================

	GLint compileResult = 0;

	glGetShaderiv(m_vertexShaderID, GL_COMPILE_STATUS, &compileResult);

	if (compileResult == GL_TRUE)
	{
		std::cout << "Shader compilation successful." << std::endl;
	}

	else
	{
		GLchar errorMessage[1000];
		GLsizei bufferSize = 1000;

		glGetShaderInfoLog(m_vertexShaderID, bufferSize, &bufferSize, errorMessage);

		std::cout << errorMessage << std::endl;
		return false;
	}

	return true;
}

void Pipeline::AttachShaders()
{
	glAttachShader(m_shaderProgramID, m_vertexShaderID);
	glAttachShader(m_shaderProgramID, m_fragmentShaderID);
}

bool Pipeline::LinkProgram()
{
	GLint linkResult = 0;

	glLinkProgram(m_shaderProgramID);
	glUseProgram(m_shaderProgramID);

	//===============================================================================

	glGetProgramiv(m_shaderProgramID, GL_LINK_STATUS, &linkResult);

	if (linkResult == GL_TRUE)
	{
		std::cout << "Shader program linking successful." << std::endl;
	}

	else
	{
		GLchar errorMessage[1000];
		GLsizei bufferSize = 1000;

		glGetProgramInfoLog(m_shaderProgramID, bufferSize, &bufferSize, errorMessage);

		std::cout << errorMessage << std::endl;
		return false;
	}

	return true;
}

void Pipeline::DetachShaders()
{
	glDetachShader(m_shaderProgramID, m_vertexShaderID);
	glDetachShader(m_shaderProgramID, m_fragmentShaderID);
}

void Pipeline::DestroyShaders()
{
	glDeleteShader(m_vertexShaderID);
	glDeleteShader(m_fragmentShaderID);
}

void Pipeline::DestroyProgram()
{
	glDeleteProgram(m_shaderProgramID);
}

