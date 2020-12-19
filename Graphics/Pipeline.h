#pragma once

#include "glad.h"
#include <string>
#include <map>
#include <glm.hpp>

class Pipeline
{
public:

	struct ShaderID
	{
		GLuint programID;
		GLuint vertexID;
		GLuint fragmentID;
		std::map<std::string, GLuint> uniforms;
	};

public:

	static Pipeline* Instance();
	enum class ShaderType { VERTEX, FRAGMENT };	

public:

	bool CreateShaderID(const std::string& vertexFile, const std::string& fragmentFile, const std::string& shaderID);
	void DetachShaders();
	void DestroyShaders();
	void DestroyProgram();
	bool UseShader(const std::string& shaderID);

public:

	bool BindAttribute(const std::string& attribute);
	bool BindUniform(const std::string& uniform);
	void BindUniforms();

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
	bool CreateProgram(GLuint& shaderProgramID);
	bool CreateShaders(GLuint& vertexShaderID, GLuint& fragmentShaderID);
	bool CompileShaders(const std::string& filename, GLuint shaderID);
	bool LinkProgram(GLuint shaderProgramID, GLuint vertexShaderID, GLuint fragmentShaderID);
	void AttachShaders(GLuint shaderProgramID, GLuint vertexShaderID, GLuint fragmentShaderID);

private:
	
	Pipeline();
	Pipeline(const Pipeline&);
	Pipeline& operator=(const Pipeline&);

private:

	ShaderID* m_shaderID;

	std::map<std::string, GLuint> m_attributes;
	std::map<std::string, ShaderID> m_shaders;

};

