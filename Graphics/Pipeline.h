#pragma once

#include "glad.h"
#include <string>
#include <map>

class Pipeline
{
public:

	static Pipeline* Instance();
	enum class ShaderType { VERTEX, FRAGMENT };
	
public:

	bool CreateProgram();
	bool CreateShaders();

	bool CompileShaders(const std::string& filename, ShaderType type);
	void AttachShaders();
	bool LinkProgram();

	void DetachShaders();
	void DestroyShaders();
	void DestroyProgram();

public:

	bool BindAttribute(const std::string& attribute);
	bool BindUniform(const std::string& uniform);

	GLuint GetProgramID();
	GLuint GetAttributeID(const std::string& attribute);
	GLuint GetUniformID(const std::string& uniform);


public:

	void SendUniformData(const std::string& uniform, GLint intData);
	void SendUniformData(const std::string& uniform, GLuint uintData);
	void SendUniformData(const std::string& uniform, GLfloat floatData);
		
	void SendUniformData(const std::string& uniform, GLfloat x, GLfloat y);
	void SendUniformData(const std::string& uniform, GLfloat x, GLfloat y, GLfloat z);
	void SendUniformData(const std::string& uniform, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

private:
	
	Pipeline();
	Pipeline(const Pipeline&);
	Pipeline& operator=(const Pipeline&);

private:

	GLuint m_shaderProgramID;
	GLuint m_vertexShaderID;
	GLuint m_fragmentShaderID;

	std::map<std::string, GLuint> m_attributes;
	std::map<std::string, GLuint> m_uniforms;

};

