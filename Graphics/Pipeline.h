#pragma once

#include "glad.h"
#include <string>
#include <map>
#include <glm.hpp>

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
		
	void SendUniformData(const std::string& uniform, const glm::vec2& vec2Data);
	void SendUniformData(const std::string& uniform, const glm::vec3& vec3Data);
	void SendUniformData(const std::string& uniform, const glm::vec4& vec4Data);

	void SendUniformData(const std::string& uniform, const glm::mat4& mat4Data, bool transpose = false);
	void SendUniformData(const std::string& uniform, const glm::mat3& mat3Data, bool transpose = false);

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

