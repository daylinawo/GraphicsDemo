#pragma once

#include "glad.h"
#include <string>

class Pipeline
{
public:

	static Pipeline* Instance();

public:

	bool CreateProgram();
	bool CreateShaders();

	bool CompileShaders(const std::string& filename);
	void AttachShaders();
	bool LinkProgram();

	void DetachShaders();
	void DestroyShaders();
	void DestroyProgram();

private:
	
	Pipeline();
	Pipeline(const Pipeline&);
	Pipeline& operator=(const Pipeline&);

private:

	GLuint m_shaderProgramID;
	GLuint m_vertexShaderID;
	GLuint m_fragmentShaderID;

};

