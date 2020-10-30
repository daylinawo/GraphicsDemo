#include "Pipeline.h"
#include "Utility.h"

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
		Utility::Log("Error creating shader program.");
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
		Utility::Log("Error creating vertex shader object.");
		system("pause");
		return false;
	}

	m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	if (!m_fragmentShaderID)
	{
		Utility::Log("Error creating fragment shader object.");
		system("pause");
		return false;
	}

	return true;
}

bool Pipeline::CompileShaders(const std::string& filename, ShaderType type)
{
	GLuint shaderID = 0;

	switch (type)
	{
		case ShaderType::VERTEX:
		{
			shaderID = m_vertexShaderID;
			break;
		}	
		case ShaderType::FRAGMENT:
		{
			shaderID = m_fragmentShaderID;
			break;
		}
	}
	std::fstream file(filename);

	if (!file)
	{
		Utility::Log("Error reading shader file.");
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
	glShaderSource(shaderID, 1, &sourceCodeC, nullptr);

	//compile vertex shader code
	glCompileShader(shaderID);

	//================================================================================

	GLint compileResult = 0;

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileResult);

	if (compileResult == GL_TRUE)
	{
		Utility::Log("Shader compilation successful.");
	}

	else
	{
		GLchar errorMessage[1000];
		GLsizei bufferSize = 1000;

		glGetShaderInfoLog(shaderID, bufferSize, &bufferSize, errorMessage);

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
		Utility::Log("Shader program linking successful.");
	}

	else
	{
		GLchar errorMessage[1000];
		GLsizei bufferSize = 1000;

		glGetProgramInfoLog(m_shaderProgramID, bufferSize, &bufferSize, errorMessage);

		Utility::Log(errorMessage);
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

bool Pipeline::BindAttribute(const std::string& attribute)
{
	if (m_attributes.find(attribute) != m_attributes.end())
	{
		Utility::Log("Vertex attribute \"" + attribute + "\" already exists.");
		return false;
	}

	GLuint vertexattributeID = glGetAttribLocation(Pipeline::Instance()->GetProgramID(),
		attribute.c_str());

	if (vertexattributeID == -1)
	{
		Utility::Log("No vertex attribute by the name of \"" + attribute + "\" exists.");
		return false;
	}

	m_attributes.insert({ attribute, vertexattributeID });

	return true;
}

bool Pipeline::BindUniform(const std::string& uniform)
{
	if (m_uniforms.find(uniform) != m_uniforms.end())
	{
		Utility::Log("Vertex uniform \"" + uniform + "\" already exists.");
		return false;
	}
	
	GLuint vertexUniformID = glGetUniformLocation(Pipeline::Instance()->GetProgramID(),
												  uniform.c_str());

	if (vertexUniformID == -1)
	{
		Utility::Log("No vertex uniform by the name of \"" + uniform + "\" exists.");
		return false;
	}

	m_uniforms.insert({ uniform, vertexUniformID });

	return true;
}

GLuint Pipeline::GetProgramID()
{
	return m_shaderProgramID;
}

GLuint Pipeline::GetAttributeID(const std::string& attribute)
{
	if (m_attributes.find(attribute) != m_attributes.end())
	{
		return m_attributes[attribute];
	}

	return -1;
}

GLuint Pipeline::GetUniformID(const std::string& uniform)
{
	if (m_uniforms.find(uniform) != m_uniforms.end())
	{
		return m_uniforms[uniform];
	}

	return -1;
}

void Pipeline::SendUniformData(const std::string& uniform, GLint intData)
{
	GLuint uniformID = GetUniformID(uniform);

	if (uniformID != -1)
	{
		glUniform1i(uniformID, intData);
	}
}

void Pipeline::SendUniformData(const std::string& uniform, GLuint uintData)
{
	GLuint uniformID = GetUniformID(uniform);

	if (uniformID != -1)
	{
		glUniform1ui(uniformID, uintData);
	}
}

void Pipeline::SendUniformData(const std::string& uniform, GLfloat floatData)
{
	GLuint uniformID = GetUniformID(uniform);

	if (uniformID != -1)
	{
		glUniform1f(uniformID, floatData);
	}
}

void Pipeline::SendUniformData(const std::string& uniform, GLfloat x, GLfloat y)
{
	GLuint uniformID = GetUniformID(uniform);

	if (uniformID != -1)
	{
		glUniform2f(uniformID, x, y);
	}
}

void Pipeline::SendUniformData(const std::string& uniform, GLfloat x, GLfloat y, GLfloat z)
{
	GLuint uniformID = GetUniformID(uniform);

	if (uniformID != -1)
	{
		glUniform3f(uniformID, x, y, z);
	}
}

void Pipeline::SendUniformData(const std::string& uniform, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	GLuint uniformID = GetUniformID(uniform);

	if (uniformID != -1)
	{
		glUniform4f(uniformID, x, y, z, w);
	}
}

