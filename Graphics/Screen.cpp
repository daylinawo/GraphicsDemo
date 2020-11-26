#include "Screen.h"
#include "Utility.h"
#include "Pipeline.h"

#include <iostream>

const float ZOOM_OUT_MAX = 90.0f;
const float ZOOM_IN_MAX = 1.0f;

Screen* Screen::Instance()
{
	static Screen* screenObject = new Screen();
	return screenObject;
}

Screen::Screen()
{
	m_width = NULL;
	m_height = NULL;
	
	m_fov = 0.0f;
	m_nearClip = 0.0f;
	m_farClip = 0.0f;

	m_window = nullptr;
	m_context = nullptr;
	m_isOutlineMode = false;
	m_projection = glm::mat4(1.0f);
}

void Screen::ClearBuffer()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Screen::SwapBuffer()
{
	SDL_GL_SwapWindow(m_window);
}

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

void Screen::SetScreen2D()
{
	//turn off depth test as we do not need this to render in 2D
	glDisable(GL_DEPTH_TEST);

	//get uniform from shader and add to map
	Pipeline::Instance()->BindUniform("projection");

	//create projection matrix
	m_projection = glm::ortho(0.0f, (float)m_width, (float)m_height, 0.0f);

	//send data to the projection uniform in shader
	Pipeline::Instance()->SendUniformData("projection", m_projection);
}

void Screen::SetScreen3D(float fov, float nearClip, float farClip)
{
	m_fov = fov;
	m_nearClip = nearClip;
	m_farClip = farClip;

	//turn on depth testing so objects are rendered in the correct order
	glEnable(GL_DEPTH_TEST);

	//hide cursor
	SDL_SetRelativeMouseMode(SDL_TRUE);

	//get uniform from shader and add to map
	Pipeline::Instance()->BindUniform("projection");

	//create projection matrix
	m_projection = glm::perspective(glm::radians(fov), (GLfloat)m_width / (GLfloat)m_height, nearClip, farClip);

	//send data to the projection uniform in shader
	Pipeline::Instance()->SendUniformData("projection", m_projection);
	
}

void Screen::SetZoom(float amount)
{
	float zoomOutMax = ZOOM_OUT_MAX;
	float zoomInMax = ZOOM_IN_MAX;

	m_fov = m_fov - amount;

	if (m_fov > zoomOutMax)
		m_fov = zoomOutMax;
	else if (m_fov < zoomInMax)
		m_fov = zoomInMax;

	//create projection matrix
	m_projection = glm::perspective(glm::radians(m_fov), (GLfloat)m_width / (GLfloat)m_height, m_nearClip, m_farClip);

	//send data to the projection uniform in shader
	Pipeline::Instance()->SendUniformData("projection", m_projection);
}

bool Screen::IsOutlineMode()
{	
	return m_isOutlineMode;
}

void Screen::SetScreenColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

int Screen::GetWidth()
{
	return m_width;
}

int Screen::GetHeight()
{
	return m_height;
}

void Screen::ResizeWindow(int width, int height)
{
	glViewport(0, 0, m_width, m_height);
}

bool Screen::Initialize(const std::string& windowName, int width, int height,
						bool fullscreen, bool coreMode, bool openGLScreen)
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

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	if (!SetupWindow(windowName, width, height, fullscreen, openGLScreen))
	{
		return false;
	}

	if (!gladLoadGL())
	{
		std::cout << "Could not load glad." << std::endl;
	}

	return true;
}

bool Screen::SetupWindow(const std::string& windowTitle, int width, 
						 int height, bool fullscreen, bool openGLScreen)
{
	Uint32 screenFlag;
	
	screenFlag = (fullscreen) ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_RESIZABLE;
	screenFlag |= (openGLScreen) ? SDL_WINDOW_OPENGL : 0;

	m_window = SDL_CreateWindow(windowTitle.c_str(),
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

	m_width = width;
	m_height = height;

	return true;
}

void Screen::DisplayProfile()
{
	std::cout << reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)) << std::endl;
	std::cout << reinterpret_cast<const char*>(glGetString(GL_VERSION)) << std::endl;
}

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

void Screen::Shutdown()
{
	//free OpenGL context
	SDL_GL_DeleteContext(m_context);

	//free game screen and window
	SDL_DestroyWindow(m_window);

	//shut down all SDL sub-systems
	SDL_Quit();
}
