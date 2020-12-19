#include "Pipeline.h"
#include "Utility.h"

#include <fstream>
#include <iostream>
#include <sstream>

Pipeline* Pipeline::Instance()
{
	static Pipeline* pipelineObject = new Pipeline();
	return pipelineObject;
}

Pipeline::Pipeline()
{
	m_shaderID = nullptr;
}
//*************************************************************
//create new shader program
//*************************************************************
bool Pipeline::CreateShaderID(const std::string& vertexFile, const std::string& fragmentFile, const std::string& shaderID)
{
	GLuint programID = 0;
	GLuint fragmentShaderID = 0;
	GLuint vertexShaderID = 0;

	if (!CreateProgram(programID))
	{
		return false;
	}

	if (!CreateShaders(vertexShaderID, fragmentShaderID))
	{
		return false;
	}

	if (!CompileShaders(vertexFile, vertexShaderID))
	{
		return false;
	}

	if (!CompileShaders(fragmentFile, fragmentShaderID))
	{
		return false;
	}

	AttachShaders(programID, vertexShaderID, fragmentShaderID);
	
	if (!LinkProgram(programID, vertexShaderID, fragmentShaderID))
	{
		return false;
	}

	m_shaders.insert(std::pair<std::string, ShaderID>(shaderID, { programID, vertexShaderID, fragmentShaderID }));

	return true;
}

bool Pipeline::UseShader(const std::string& shaderID)
{
	auto it = m_shaders.find(shaderID);

	if (it != m_shaders.end())
	{
		m_shaderID = &it->second;
		glUseProgram(m_shaderID->programID);
	}
	else
	{
		Utility::Log("Could not find shader program ID: " + shaderID);
		return false;
	}

	return true;
}


bool Pipeline::CreateProgram(GLuint& programID)
{
	programID = glCreateProgram();

	if (!programID)
	{
		Utility::Log("Error creating shader program.");
		system("pause");
		return false;
	}

	return true;
}

bool Pipeline::CreateShaders(GLuint& vertexShaderID, GLuint& fragmentShaderID)
{
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

	if (!vertexShaderID)
	{
		Utility::Log("Error creating vertex shader object.");
		system("pause");
		return false;
	}

	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	if (!fragmentShaderID)
	{
		Utility::Log("Error creating fragment shader object.");
		system("pause");
		return false;
	}

	return true;
}

bool Pipeline::CompileShaders(const std::string& filename, GLuint shaderID)
{
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

	//bind source code to shader object
	glShaderSource(shaderID, 1, &sourceCodeC, nullptr);

	//compile shader code
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

void Pipeline::AttachShaders(GLuint programID, GLuint vertexShaderID, GLuint fragmentShaderID)
{
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
}

bool Pipeline::LinkProgram(GLuint programID, GLuint vertexShaderID, GLuint fragmentShaderID)
{
	GLint linkResult = 0;

	glLinkProgram(programID);

	//===============================================================================

	glGetProgramiv(programID, GL_LINK_STATUS, &linkResult);

	if (linkResult == GL_TRUE)
	{
		Utility::Log("Shader program linking successful.");
	}

	else
	{
		GLchar errorMessage[1000];
		GLsizei bufferSize = 1000;

		glGetProgramInfoLog(programID, bufferSize, &bufferSize, errorMessage);

		Utility::Log(errorMessage);
		return false;
	}

	return true;
}

void Pipeline::DetachShaders()
{
	for (auto it = m_shaders.begin(); it != m_shaders.end(); it++)
	{
		glDetachShader(it->second.programID, it->second.vertexID);
		glDetachShader(it->second.programID, it->second.fragmentID);
	}
}

void Pipeline::DestroyShaders()
{
	for (auto it = m_shaders.begin(); it != m_shaders.end(); it++)
	{
		glDeleteShader(it->second.vertexID);
		glDeleteShader(it->second.fragmentID);
	}
}

void Pipeline::DestroyProgram()
{
	for (auto it = m_shaders.begin(); it != m_shaders.end(); it++)
	{
		glDeleteProgram(it->second.programID);
	}
}

GLuint Pipeline::GetProgramID()
{
	return m_shaderID->programID;
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
	if (m_shaderID->uniforms.find(uniform) != m_shaderID->uniforms.end())
	{
		return m_shaderID->uniforms[uniform];
	}

	return -1;
}

bool Pipeline::BindAttribute(const std::string& attribute)
{
	if (m_attributes.find(attribute) != m_attributes.end())
	{
		//Utility::Log("Vertex attribute \"" + attribute + "\" already exists.");
		return false;
	}

	GLuint vertexAttributeID = glGetAttribLocation(Pipeline::Instance()->GetProgramID(),
												   attribute.c_str());

	if (vertexAttributeID == -1)
	{
		Utility::Log("No vertex attribute by the name of \"" + attribute + "\" exists.");
		return false;
	}

	m_attributes.insert(std::pair<std::string, GLuint>(attribute, vertexAttributeID));


	return true;
}

bool Pipeline::BindUniform(const std::string& uniform)
{
	if (m_shaderID->uniforms.find(uniform) != m_shaderID->uniforms.end())
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

	m_shaderID->uniforms.insert(std::pair<std::string, GLuint>( uniform, vertexUniformID));
	Utility::Log("Binded uniform: " + uniform);
	return true;
}

void Pipeline::BindUniforms()
{
	GLint totalUniforms, maxNameLength; 
	glGetProgramiv(m_shaderID->programID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxNameLength);
	glGetProgramiv(m_shaderID->programID, GL_ACTIVE_UNIFORMS, &totalUniforms);

	GLsizei length;
	GLenum type; 

	GLchar* name = new GLchar[maxNameLength]; // variable name in GLSL

	for (GLuint i = 0; i < totalUniforms; i++)
	{
		glGetActiveUniformName(m_shaderID->programID, i, maxNameLength, &length, name);
		std::string _name(name);
		BindUniform(_name);
	}

	delete[] name;
}

void Pipeline::SendUniformData(const std::string& uniform, GLint intData)
{
	glUniform1i(GetUniformID(uniform), intData);
}

void Pipeline::SendUniformData(const std::string& uniform, GLuint uintData)
{
	glUniform1ui(GetUniformID(uniform), uintData);
}

void Pipeline::SendUniformData(const std::string& uniform, GLfloat floatData)
{
	glUniform1f(GetUniformID(uniform), floatData);
}

void Pipeline::SendUniformData(const std::string& uniform, const glm::vec2& vec2Data)
{
	glUniform2fv(GetUniformID(uniform), 1, &vec2Data.x);
}

void Pipeline::SendUniformData(const std::string& uniform, const glm::vec3& vec3Data)
{
	glUniform3fv(GetUniformID(uniform), 1, &vec3Data.x);
}

void Pipeline::SendUniformData(const std::string& uniform, const glm::vec4& vec4Data)
{
	glUniform4fv(GetUniformID(uniform), 1, &vec4Data.x);
}

void Pipeline::SendUniformData(const std::string& uniform, const glm::mat4& mat4Data, bool transpose)
{
	GLboolean _transpose = (transpose) ? GL_TRUE : GL_FALSE;

	glUniformMatrix4fv(GetUniformID(uniform), 1, _transpose, &mat4Data[0][0]);
}

void Pipeline::SendUniformData(const std::string& uniform, const glm::mat3& mat3Data, bool transpose)
{
	GLboolean _transpose = (transpose) ? GL_TRUE : GL_FALSE;

	glUniformMatrix3fv(GetUniformID(uniform), 1, _transpose, &mat3Data[0][0]);
}

