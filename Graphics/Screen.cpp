#include "Screen.h"
#include "Utility.h"
#include "Pipeline.h"

#include <iostream>

Screen* Screen::Instance()
{
	static Screen* screenObject = new Screen();
	return screenObject;
}

Screen::Screen()
{
	m_width = 0;
	m_height = 0;

	m_window = nullptr;
	m_context = nullptr;
	m_isOutlineMode = false;
	m_projection = glm::mat4(1.0f);
}
//*******************************************************************
// creates a 2D orthogonal projection
//*******************************************************************
void Screen::SetScreen2D()
{
	//turn off depth test as we do not need this to render in 2D
	glDisable(GL_DEPTH_TEST);

	//create projection matrix
	m_projection = glm::ortho(0.0f, (float)m_width, 0.0f, (float)m_height);

	//send projection matrix to shader
	Pipeline::Instance()->SendUniformData("projection", m_projection);
}
//*******************************************************************
// creates a 3D perspective projection
//*******************************************************************
void Screen::SetScreen3D(GLfloat fov, GLfloat nearClip, GLfloat farClip)
{
	//turn on depth testing so objects are rendered in the correct order
	glEnable(GL_DEPTH_TEST);

	//hide cursor
	SDL_SetRelativeMouseMode(SDL_TRUE);

	//create projection matrix
	m_projection = glm::perspective(glm::radians(fov), (GLfloat)m_width / (GLfloat)m_height, nearClip, farClip);

	//send projection matrix to shader
	Pipeline::Instance()->SendUniformData("projection", m_projection);
}
//*******************************************************************
// creates an SDL window with OpenGL context
//*******************************************************************
bool Screen::Initialize(const std::string& windowName, int width, int height, bool fullscreen, bool coreMode)
{

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) == -1)
	{
		std::cout << "Could not initialize SDL." << std::endl;
		return false;
	}

	//Set RGBA buffer sizes and total buffer size
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

	//enable double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	int mode = (coreMode) ? static_cast<int>(SDL_GL_CONTEXT_PROFILE_CORE) :
							static_cast<int>(SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

	//set a compatibility OpenGL context
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, mode);

	//set major and minor version of OpenGL context
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	Uint32 screenFlag = SDL_WINDOW_OPENGL;

	screenFlag |= (fullscreen) ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_RESIZABLE;

	m_window = SDL_CreateWindow(windowName.c_str(),
								SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED,
								width, height,
								screenFlag);

	if (!m_window)
	{
		std::cout << "Window could not be created." << std::endl;
		return false;
	}

	m_context = SDL_GL_CreateContext(m_window);

	if (!m_context)
	{
		std::cout << "OpenGL context could not be created." << std::endl;
		return false;
	}

	if (!gladLoadGL())
	{
		std::cout << "Could not load glad." << std::endl;
		return false;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_width = width;
	m_height = height;

	return true;
}
//*******************************************************************
// displays the supported OpenGL hardware
//*******************************************************************
void Screen::DisplayProfile()
{
	std::cout << reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)) << std::endl;
	std::cout << reinterpret_cast<const char*>(glGetString(GL_VERSION)) << std::endl;
}
//*******************************************************************
// displays list of supported openGL extensions
//*******************************************************************
void Screen::DisplayExtensions()
{
	GLint totalExtensions;
	glGetIntegerv(GL_NUM_EXTENSIONS, &totalExtensions);

	for (GLint i = 0; i < totalExtensions; i++)
	{
		std::cout << "Extension #" << i << " : "
			<< reinterpret_cast<const char*>(glGetStringi(GL_EXTENSIONS, i)) << std::endl;
	}
}
//*******************************************************************
// clears frame buffer
//*******************************************************************
void Screen::ClearBuffer()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
//*******************************************************************
// swaps frame buffer if double buffer is supported
//*******************************************************************
void Screen::SwapBuffer()
{
	SDL_GL_SwapWindow(m_window);
}
//*******************************************************************
// toggles outline mode on and off
//*******************************************************************
void Screen::SetOutlineMode(bool flag)
{
	switch (flag)
	{
	case true:
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		m_isOutlineMode = true;
		break;
	}
	case false:
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		m_isOutlineMode = false;
		break;
	}
	}
}
//*******************************************************************
// sets rgba values that GLclear uses to clear the color buffers
//*******************************************************************
void Screen::SetScreenColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}
//*******************************************************************
// returns screen resolution
//*******************************************************************
glm::vec2 Screen::GetResolution()
{
	return glm::vec2(m_width, m_height);
}
//*******************************************************************
// sets viewport resolution
//*******************************************************************
void Screen::ResizeWindow(int width, int height)
{
	glViewport(0, 0, m_width, m_height);
}
//*******************************************************************
// returns a boolean of the state of outline mode
//*******************************************************************
bool Screen::IsOutlineMode()
{	
	return m_isOutlineMode;
}
//*******************************************************************
// shuts down SDL, openGL and destroys window
//*******************************************************************
void Screen::Shutdown()
{
	//free OpenGL context
	SDL_GL_DeleteContext(m_context);

	//free game screen and window
	SDL_DestroyWindow(m_window);

	//shut down all SDL sub-systems
	SDL_Quit();
}
